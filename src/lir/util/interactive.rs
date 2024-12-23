
use std::{
    collections::VecDeque, fmt::{Display, Formatter},
    io::{Read, Write}
};
use crate::lir::{Interface, Symbol};
use anyhow::Result;

#[derive(Default)]
pub struct InteractiveInterface;

impl InteractiveInterface {
    pub fn new() -> Self {
        Self::default()
    }
}

impl Interface for InteractiveInterface {
    fn has_extern(&self, name: &str) -> bool {
        match name {
            "fadd"
            | "fsub"
            | "fmul"
            | "fdiv"
            | "frem"
            | "flt"
            | "add"
            | "mul"
            | "div"
            | "lt"
            | "eq"
            | "put"
            | "putnum"
            | "fprint"
            | "to_float"
            | "to_int"
            | "round"
            | "floor"
            | "ceil"
            | "deref"
            | "idx"
            | "malloc"
            | "free" => true,

            _ => false,
        }
    }

    fn external_call(&mut self, name: &str, args: Vec<i64>) -> Result<i64> {
        Ok(match name {
            "put" => {
                print!("{}", args[0] as u8 as char);
                0
            },
            "putnum" => {
                for ch in args[0].to_string().bytes() {
                    print!("{}", ch as char);
                }
                0
            },
            "fprint" => {
                for ch in f64::from_bits(args[0] as u64).to_string().bytes() {
                    print!("{}", ch as char);
                }
                0
            },
            "idx" => {
                let ptr = args[0] as *const i64;
                let idx = args[1] as usize;
                unsafe {
                    *ptr.add(idx)
                }
            },
            "malloc" => {
                let size = args[0] as usize;
                // Call malloc
                let ptr = Box::into_raw(vec![0 as i64; size].into_boxed_slice());
                unsafe {
                    ptr as *const i64 as i64
                }
            },
            "free" => {
                let ptr = args[0] as *mut i64;
                let _ = unsafe { Box::from_raw(ptr) };
                0
            },
            "fadd" => f64::to_bits(f64::from_bits(args[0] as u64) + f64::from_bits(args[1] as u64)) as i64,
            "fsub" => f64::to_bits(f64::from_bits(args[0] as u64) - f64::from_bits(args[1] as u64)) as i64,
            "fmul" => f64::to_bits(f64::from_bits(args[0] as u64) * f64::from_bits(args[1] as u64)) as i64,
            "fdiv" => f64::to_bits(f64::from_bits(args[0] as u64) / f64::from_bits(args[1] as u64)) as i64,
            "fneg" => f64::to_bits(-f64::from_bits(args[0] as u64)) as i64,
            "frem" => f64::to_bits(f64::from_bits(args[0] as u64) % f64::from_bits(args[1] as u64)) as i64,
            "flt" => if f64::from_bits(args[0] as u64) < f64::from_bits(args[1] as u64) { 1 } else { 0 },
            "lt" => if args[0] < args[1] { 1 } else { 0 },

            "add" => args[0] + args[1],
            "sub" => args[0] - args[1],
            "div" => args[0] / args[1],
            "mul" => args[0] * args[1],

            "eq" => if args[0] == args[1] { 1 } else { 0 },
            
            "round" => f64::to_bits(f64::from_bits(args[0] as u64).round()) as i64,
            "floor" => f64::to_bits(f64::from_bits(args[0] as u64).floor()) as i64,
            "ceil" => f64::to_bits(f64::from_bits(args[0] as u64).ceil()) as i64,
            
            "to_float" => f64::to_bits(args[0] as f64) as i64,
            "to_int" => f64::from_bits(args[0] as u64) as i64,
            _ => anyhow::bail!("Unknown external function: {}", name),
        })
    }
}