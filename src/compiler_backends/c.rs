use anyhow::Result;
use crate::{CompileTarget, Expr, Stmt, Env, lift_global_decls};
use std::fmt::Write;

pub struct C;

impl C {
    pub fn new() -> Self {
        Self
    }
}

impl CompileTarget for C {
    fn has_extern(&self, name: &str) -> bool {
        true
    }

    fn compile(&mut self, program: Stmt) -> Result<String> {
        let (procs, program) = lift_global_decls(vec![program]);
        let env = Env::new();
        // self.compile_stmt(&Stmt::Block(program), &env)
        
        let mut prelude = String::from("#include <stdint.h>\nint64_t mage_as_int(double x) {{ return *(int64_t*)&x; }}\n\n#if __has_include(\"ffi.h\")\n#include \"ffi.h\"\n#endif\n\n/* BEGIN PROCEDURES */");

        let mut result = String::new();
        // Compile the lifted procedures
        for stmt in procs {
            write!(prelude, "{}\n", self.compile_stmt(&stmt, &env)?)?;
        }

        // Compile the main program
        write!(result, "{}", self.compile_stmt(&Stmt::Block(program), &env)?)?;

        Ok(format!("{}\n/* BEGIN MAIN */\nint main() {{\n{}\n}}", prelude, result))
    }
}