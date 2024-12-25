use std::{
    collections::HashMap,
    fmt::{Display, Debug, Formatter, Result as FmtResult},
    sync::{Arc, RwLock},
};

use lazy_static::lazy_static;

lazy_static! {
    static ref SYMBOLS: RwLock<HashMap<String, Symbol>> = RwLock::new(HashMap::new());
}

/// A symbol that uses string interning
#[allow(clippy::derived_hash_with_manual_eq, clippy::derive_ord_xor_partial_ord)]
#[derive(Clone, Hash, Eq, Ord)]
pub struct Symbol(Arc<String>);

impl Symbol {
    /// Create a new symbol
    pub fn new(name: &str) -> Self {
        let mut symbols = SYMBOLS.write().unwrap();
        if let Some(symbol) = symbols.get(name) {
            return symbol.clone();
        }

        let symbol = Symbol(Arc::new(name.to_string()));
        symbols.insert(name.to_string(), symbol.clone());
        symbol
    }

    /// Get the name of the symbol
    pub fn name(&self) -> &str {
        &self.0
    }

    /// Get an iterator over all symbols
    pub fn all_symbols() -> Vec<Symbol> {
        SYMBOLS.read().unwrap().values().cloned().collect()
    }
}

impl From<&str> for Symbol {
    fn from(s: &str) -> Self {
        Symbol::new(s)
    }
}

impl From<String> for Symbol {
    fn from(s: String) -> Self {
        Symbol::new(&s)
    }
}

impl PartialEq for Symbol {
    fn eq(&self, other: &Self) -> bool {
        if Arc::ptr_eq(&self.0, &other.0) {
            return true;
        }
        self.0 == other.0
    }
}

#[allow(clippy::non_canonical_partial_ord_impl)]
impl PartialOrd for Symbol {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        if Arc::ptr_eq(&self.0, &other.0) {
            return Some(std::cmp::Ordering::Equal);
        }
        self.0.partial_cmp(&other.0)
    }
}

impl Debug for Symbol {
    fn fmt(&self, f: &mut Formatter) -> FmtResult {
        write!(f, "{}", self.0)
    }
}

impl Display for Symbol {
    fn fmt(&self, f: &mut Formatter) -> FmtResult {
        write!(f, "{}", self.0)
    }
}

impl AsRef<str> for Symbol {
    fn as_ref(&self) -> &str {
        &self.0
    }
}