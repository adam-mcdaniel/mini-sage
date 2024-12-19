use anyhow::Result;
use crate::{Env, Expr, Stmt, Symbol};

mod llvm;
pub use llvm::*;

mod c;
pub use c::*;

fn wrap_symbol_name(name: &Symbol) -> String {
    format!("_{}", name)
}


pub(super) fn lift_global_decls(stmts: Vec<Stmt>) -> (Vec<Stmt>, Vec<Stmt>) {
    let mut new_stmts: Vec<Stmt> = Vec::new();
    let mut globals = Vec::new();
    for stmt in stmts {
        match stmt {
            Stmt::Annotated(metadata, stmt) => {
                let (new_procs, new_new_stmts) = lift_global_decls(vec![*stmt]);
                globals.extend(new_procs.into_iter().map(|stmt| stmt.annotate(metadata.clone())));
                new_stmts.extend(new_new_stmts);
            }
            Stmt::DeclareProc { .. } => {
                globals.push(stmt);
            }
            Stmt::ExternProc { .. } => {
                globals.push(stmt);
            }
            Stmt::DeclareVar { is_static: true, .. } => {
                globals.push(stmt);
            }
            Stmt::Block(stmts) => {
                let (new_procs, new_new_stmts) = lift_global_decls(stmts);
                globals.extend(new_procs);
                new_stmts.extend(new_new_stmts);
            }
            stmt => new_stmts.push(stmt),
        }
    }
    (globals, new_stmts)
}

pub trait CompileTarget {
    fn has_extern(&self, name: &str) -> bool;

    fn compile(&mut self, program: Stmt) -> Result<String> {
        let (procs, stmts) = lift_global_decls(vec![program]);
        let env = Env::new();
        let mut code = String::new();
        for proc in procs {
            code.push_str(&self.compile_stmt(&proc, &env)?);
            code.push_str("\n");
        }
        code.push_str(&self.compile_stmt(&Stmt::Block(stmts), &env)?);
        Ok(code)
    }
    
    fn compile_expr(&mut self, expr: &Expr, env: &Env) -> Result<String> {
        match expr {
            Expr::Annotated(_, expr) => self.compile_expr(expr, env),
            Expr::If(cond, then, else_) => {
                let cond = self.compile_expr(cond, env)?;
                let then = self.compile_expr(then, env)?;
                let else_ = self.compile_expr(else_, env)?;
                Ok(format!("{}? {} : {}", cond, then, else_))
            }
            Expr::Int(value) => Ok(format!("{value:?}")),
            Expr::Char(value) => Ok(format!("{value:?}")),
            Expr::Float(value) => Ok(format!("mage_as_int({value:?})")),
            Expr::Bool(value) => Ok(if *value { "true" } else { "false" }.to_string()),
            Expr::Var(name) => Ok(wrap_symbol_name(name)),
            Expr::Ref(name) => Ok(format!("((int64_t)&{})", wrap_symbol_name(name))),
            Expr::App(func, args) => {
                let func = self.compile_expr(func, env)?;
                let args = args.iter().map(|arg| self.compile_expr(arg, env)).collect::<Result<Vec<_>>>()?;
                Ok(format!("{}({})", func, args.join(", ")))
            }
        }
    }

    fn compile_stmt(&mut self, stmt: &Stmt, env: &Env) -> Result<String> {
        match stmt {
            Stmt::Annotated(metadata, stmt) => {
                let stmt = self.compile_stmt(stmt, env)?;
                Ok(format!("/* {} */\n{}", metadata, stmt))
            }
            Stmt::Expr(expr) => Ok(format!("{};", self.compile_expr(expr, env)?)),
            Stmt::Return(value) => {
                let value = self.compile_expr(value, env)?;
                Ok(format!("return {};", value))
            }
            Stmt::Continue => Ok("continue;".to_string()),
            Stmt::Break => Ok("break;".to_string()),
            Stmt::DeclareVar { name, is_static, value } => {
                let name = wrap_symbol_name(name);
                let value = self.compile_expr(value, env)?;
                if *is_static {
                    Ok(format!("static int64_t {} = {};", name, value))
                } else {
                    Ok(format!("int64_t {} = {};", name, value))
                }
            }
            Stmt::DeclareProc { name, args, body } => {
                let name = wrap_symbol_name(name);
                let new_env = env.new_scope();
                let args = args.iter().map(|arg| format!("int64_t {}", wrap_symbol_name(arg))).collect::<Vec<_>>().join(", ");
                let body = self.compile_stmt(body, &new_env)?;
                Ok(format!("int64_t {}({}) {{\n{}\n}}", name, args, body))
            }
            Stmt::ExternProc { name, args, body } => {
                if self.has_extern(name.as_ref()) {
                    let name = wrap_symbol_name(name);
                    let args = args.iter().map(|arg| format!("int64_t {}", arg)).collect::<Vec<_>>().join(", ");
                    Ok(format!("int64_t {}({});", name, args))
                } else if let Some(body) = body {
                    // Use the body as a fallback
                    self.compile_stmt(&Stmt::DeclareProc { name: name.clone(), args: args.clone(), body: body.clone() }, env)
                } else {
                    Err(anyhow::anyhow!("Undefined external procedure: {}", name))
                }
            }
            Stmt::AssignVar(name, value) => {
                let name = wrap_symbol_name(name);
                let value = self.compile_expr(value, env)?;
                Ok(format!("{} = {};", name, value))
            }
            Stmt::AssignRef(dst, src) => {
                let dst = self.compile_expr(dst, env)?;
                let src = self.compile_expr(src, env)?;
                Ok(format!("*(int64_t*){} = {};", dst, src))
            }
            Stmt::While(cond, body_) => {
                let cond = self.compile_expr(cond, env)?;
                let body = self.compile_stmt(body_, env)?;
                Ok(format!("while ({}) {{\n{}\n}}", cond, body))
            }
            Stmt::If(cond, then, else_) => {
                let cond = self.compile_expr(cond, env)?;
                let then = self.compile_stmt(then, env)?;
                let else_ = self.compile_stmt(else_, env)?;
                Ok(format!("if ({}) {{\n{}\n}} else {{\n{}\n}}", cond, then, else_))
            }

            Stmt::Block(stmts) => {
                let stmts = stmts.iter().map(|stmt| self.compile_stmt(stmt, env)).collect::<Result<Vec<_>>>()?;
                Ok(stmts.join("\n"))
            }
        }
    }
}
