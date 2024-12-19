use anyhow::Result;
use lazy_static::lazy_static;
use std::{
    collections::{HashMap, HashSet}, io::Write, path::Display, sync::{Mutex, RwLock}
};

mod symbol;
pub use symbol::Symbol;

mod parser;
pub use parser::parse;

mod interpreter;
pub use interpreter::*;

mod util;
pub use util::*;

#[derive(Debug, Clone)]
pub struct SourceCodeLocation {
    line: usize,
    column: usize,
    length: usize,
}

mod compiler_backends;
pub use compiler_backends::*;

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub struct ID {
    id: usize,
}

lazy_static! {
    static ref IDS: RwLock<HashMap<String, ID>> = RwLock::new(HashMap::new());
    static ref NAMES: RwLock<HashMap<ID, String>> = RwLock::new(HashMap::new());
}

impl ID {
    fn create() -> Self {
        lazy_static! {
            static ref COUNTER: Mutex<usize> = Mutex::new(0);
        }

        let mut counter = COUNTER.lock().unwrap();
        *counter += 1;
        Self { id: *counter }
    }

    pub fn new(name: &str) -> Self {
        // Check if it already exists
        {
            let ids = IDS.read().unwrap();
            if let Some(id) = ids.get(name) {
                return *id;
            }
        }

        // Create a new one
        let id = Self::create();
        let mut ids = IDS.write().unwrap();
        ids.insert(name.to_string(), id);
        let mut names = NAMES.write().unwrap();
        names.insert(id, name.to_string());
        id
    }

    pub fn get_name(&self) -> String {
        let names = NAMES.read().unwrap();
        names.get(self).unwrap().clone()
    }
}


// #[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
// pub struct Register {
//     register_id: ID,
//     scope_id: Option<ID>,
// }

// impl Register {
//     pub fn is_static(&self) -> bool {
//         self.scope_id.is_none()
//     }

//     pub fn new(name: &str) -> Self {
//         Self {
//             register_id: ID::new(name),
//             scope_id: None,
//         }
//     }

//     pub fn get_name(&self) -> String {
//         format!(
//             "{}_{}_{}",
//             self.register_id.get_name(),
//             self.register_id.id.to_string(),
//             self.scope_id.map_or(String::new(), |id| id.id.to_string())
//         )
//     }

//     pub fn new_in_scope(name: &str, scope_id: ID) -> Self {
//         Self {
//             register_id: ID::new(name),
//             scope_id: Some(scope_id),
//         }
//     }

//     pub fn with_scope(&self, scope_id: ID) -> Self {
//         Self {
//             register_id: self.register_id,
//             scope_id: Some(scope_id),
//         }
//     }
// }


#[derive(Debug, Clone)]
pub enum Metadata {
    Many(Vec<Self>),
    Location(SourceCodeLocation),
}

impl std::fmt::Display for Metadata {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Metadata::Many(metadata) => {
                for m in metadata {
                    write!(f, "{}", m)?;
                }
                Ok(())
            }
            Metadata::Location(location) => {
                write!(f, "line: {}, column: {}, length: {}", location.line, location.column, location.length)
            }
        }
    }
}

impl From<SourceCodeLocation> for Metadata {
    fn from(location: SourceCodeLocation) -> Self {
        Metadata::Location(location)
    }
}

#[derive(Debug, Clone)]
pub enum Expr {
    Annotated(Metadata, Box<Self>),
    If(Box<Self>, Box<Self>, Box<Self>),
    Int(i64),
    Char(char),
    Float(f64),
    Bool(bool),
    Var(Symbol),
    Ref(Symbol),
    App(Box<Self>, Vec<Self>),
}

impl Expr {
    pub fn annotate(self, metadata: impl Into<Metadata>) -> Self {
        Self::Annotated(metadata.into(), Box::new(self))
    }

    pub fn strip_annotations(&self) -> &Self {
        match self {
            Self::Annotated(_, expr) => expr.strip_annotations(),
            _ => self,
        }
    }
}

pub fn ref_(name: impl ToString) -> Expr {
    Expr::Ref(name.to_string().into())
}

pub fn var(name: impl ToString) -> Expr {
    Expr::Var(name.to_string().into())
}

pub fn if_expr(cond: impl Into<Expr>, then: impl Into<Expr>, else_: impl Into<Expr>) -> Expr {
    Expr::If(Box::new(cond.into()), Box::new(then.into()), Box::new(else_.into()))
}

pub fn app(func: impl Into<Expr>, args: Vec<impl Into<Expr>>) -> Expr {
    let func = func.into();
    let args = args.into_iter().map(|arg| arg.into()).collect();
    Expr::App(Box::new(func), args)
}

impl Expr {
    pub fn app(self, args: Vec<Self>) -> Self {
        Self::App(Box::new(self), args)
    }
}

impl From<String> for Expr {
    fn from(value: String) -> Self {
        Expr::Var(value.into())
    }
}

impl From<&str> for Expr {
    fn from(value: &str) -> Self {
        Expr::Var(value.into())
    }
}

impl From<i64> for Expr {
    fn from(value: i64) -> Self {
        Self::Int(value)
    }
}

impl From<char> for Expr {
    fn from(value: char) -> Self {
        Self::Char(value)
    }
}

impl From<f64> for Expr {
    fn from(value: f64) -> Self {
        Self::Float(value)
    }
}

impl From<bool> for Expr {
    fn from(value: bool) -> Self {
        Self::Bool(value)
    }
}

#[derive(Debug, Clone)]
pub enum Stmt {
    Annotated(Metadata, Box<Self>),
    Expr(Expr),
    Return(Expr),
    Continue,
    Break,
    DeclareVar {
        name: Symbol,
        is_static: bool,
        value: Box<Expr>,
    },
    DeclareProc {
        name: Symbol,
        args: Vec<Symbol>,
        body: Box<Stmt>,
    },
    ExternProc {
        name: Symbol,
        args: Vec<Symbol>,
        body: Option<Box<Stmt>>,
    },
    AssignVar(Symbol, Box<Expr>),
    AssignRef(Box<Expr>, Box<Expr>),
    While(Box<Expr>, Box<Self>),
    If(Box<Expr>, Box<Self>, Box<Self>),
    Block(Vec<Self>),
}

impl Stmt {
    pub fn annotate(self, metadata: impl Into<Metadata>) -> Self {
        Self::Annotated(metadata.into(), Box::new(self))
    }

    pub fn strip_annotations(&self) -> &Self {
        match self {
            Self::Annotated(_, stmt) => stmt.strip_annotations(),
            _ => self,
        }
    }
}

pub fn let_var(name: impl ToString, value: impl Into<Expr>) -> Stmt {
    Stmt::DeclareVar {
        name: Symbol::new(&name.to_string()),
        is_static: false,
        value: Box::new(value.into()),
    }
}

pub fn let_static(name: impl ToString, value: impl Into<Expr>) -> Stmt {
    Stmt::DeclareVar {
        name: Symbol::new(&name.to_string()),
        is_static: true,
        value: Box::new(value.into()),
    }
}

pub fn proc(name: impl ToString, args: Vec<impl ToString>, body: impl Into<Stmt>) -> Stmt {
    Stmt::DeclareProc {
        name: Symbol::new(&name.to_string()),
        args: args.into_iter().map(|arg| Symbol::new(&arg.to_string())).collect(),
        body: Box::new(body.into()),
    }
}

pub fn extern_proc(name: impl ToString, args: Vec<impl ToString>, body: Option<Stmt>) -> Stmt {
    Stmt::ExternProc {
        name: Symbol::new(&name.to_string()),
        args: args.into_iter().map(|arg| Symbol::new(&arg.to_string())).collect(),
        body: body.map(Box::new),
    }
}

pub fn assign_var(name: impl Into<Symbol>, value: impl Into<Expr>) -> Stmt {
    Stmt::AssignVar(name.into(), Box::new(value.into()))
}

pub fn assign_ref(dst: impl Into<Expr>, src: impl Into<Expr>) -> Stmt {
    Stmt::AssignRef(Box::new(dst.into()), Box::new(src.into()))
}

pub fn while_(cond: impl Into<Expr>, body: impl Into<Stmt>) -> Stmt {
    Stmt::While(Box::new(cond.into()), Box::new(body.into()))
}

fn if_(cond: impl Into<Expr>, then: impl Into<Stmt>, else_: impl Into<Stmt>) -> Stmt {
    Stmt::If(Box::new(cond.into()), Box::new(then.into()), Box::new(else_.into()))
}

fn return_(value: impl Into<Expr>) -> Stmt {
    Stmt::Return(value.into())
}

pub fn block(stmts: Vec<Stmt>) -> Stmt {
    Stmt::Block(stmts)
}

pub fn stmt(expr: impl Into<Expr>) -> Stmt {
    Stmt::Expr(expr.into())
}

pub struct Env {
    locals: HashSet<Symbol>,
    statics: HashSet<Symbol>,
    scope: ID,
}

impl Env {
    pub fn new() -> Self {
        Self {
            locals: HashSet::new(),
            statics: HashSet::new(),
            scope: ID::create(),
        }
    }

    pub fn new_scope(&self) -> Self {
        Self {
            locals: HashSet::new(),
            statics: self.statics.clone(),
            scope: ID::create(),
        }
    }
}

