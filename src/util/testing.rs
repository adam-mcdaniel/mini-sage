
use std::{
    collections::VecDeque, fmt::{Display, Formatter}
};
use crate::{Interface, Symbol};
use anyhow::Result;

#[derive(Debug, Default)]
pub struct TestInterface {
    pub input: VecDeque<i64>,
    pub output: Vec<i64>,
}

impl TestInterface {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn with_input(mut self, input: Vec<i64>) -> Self {
        self.input = input.into();
        self
    }

    pub fn with_string_input(mut self, input: &str) -> Self {
        self.input = input.bytes().map(|x| x as i64).collect();
        self
    }
}

impl Display for TestInterface {
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        // Try to convert output to string
        let mut input = self.input.iter().map(|x| *x as u8).collect::<Vec<u8>>();
        let mut output = self.output.iter().map(|x| *x as u8).collect::<Vec<u8>>();
        // Remove trailing zeros
        while let Some(&0) = output.last() {
            output.pop();
        }
        while let Some(&0) = input.last() {
            input.pop();
        }
        /*
        match (String::from_utf8(input), String::from_utf8(output)) {
            (Ok(input), Ok(output)) => write!(f, "Remaining Input: {}\nOutput: {}", input, output),
            (Err(_), Ok(output)) => write!(f, "Remaining Input: {:?}\nOutput: {}", self.input, output),
            (Ok(input), Err(_)) => write!(f, "Remaining Input: {}\nOutput: {:?}", input, self.output),
            (Err(_), Err(_)) => write!(f, "Remaining Input: {:?}\nOutput: {:?}", self.input, self.output),
        }
        */
        write!(f, "{}", String::from_utf8_lossy(&output))
    }
}
// extern fun fadd(x, y);
// extern fun fsub(x, y);
// extern fun fmul(x, y);
// extern fun fdiv(x, y);
// extern fun frem(x, y);
// extern fun flt(x, y);

// extern fun add(x, y);
// extern fun mul(x, y);
// extern fun div(x, y);
// extern fun lt(x, y);
// extern fun eq(x, y);

// extern fun put(ch);
// extern fun putnum(n);
// extern fun fprint(ch);
// fun newline() {
//     put('\n');
// }

// extern fun to_float(n);
// extern fun to_int(n);
// extern fun round(n);
// extern fun floor(n);
// extern fun ceil(n);

// extern fun deref(ptr);
impl Interface for TestInterface {
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
            | "deref" => true,

            _ => false,
        }
    }

    fn external_call(&mut self, name: &str, args: Vec<i64>) -> Result<i64> {
        Ok(match name {
            "put" => {
                self.output.push(args[0]);
                0
            },
            "putnum" => {
                for ch in args[0].to_string().bytes() {
                    self.output.push(ch as i64);
                }
                0
            },
            "fprint" => {
                for ch in f64::from_bits(args[0] as u64).to_string().bytes() {
                    self.output.push(ch as i64);
                }
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

            "eq" => if args[0] == args[1] { 1 } else { 0 },
            "add" => args[0] + args[1],
            "sub" => args[0] - args[1],
            "mul" => args[0] * args[1],
            "div" => args[0] / args[1],
            
            "deref" => args[0],
            
            "round" => f64::to_bits(f64::from_bits(args[0] as u64).round()) as i64,
            "floor" => f64::to_bits(f64::from_bits(args[0] as u64).floor()) as i64,
            "ceil" => f64::to_bits(f64::from_bits(args[0] as u64).ceil()) as i64,
            
            "to_float" => f64::to_bits(args[0] as f64) as i64,
            "to_int" => f64::from_bits(args[0] as u64) as i64,
            _ => anyhow::bail!("Unknown external function: {}", name),
        })
    }
}