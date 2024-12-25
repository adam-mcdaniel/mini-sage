
use std::{
    collections::VecDeque, fmt::{Display, Formatter}
};
use crate::Interface;
use anyhow::Result;
use std::collections::HashMap;
use lazy_static::lazy_static;


#[derive(Debug, Default)]
pub struct TestInterface {
    pub input: VecDeque<u8>,
    pub output: Vec<u8>,
}

impl TestInterface {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn with_input(mut self, input: Vec<u8>) -> Self {
        self.input = input.into();
        self
    }

    pub fn with_string_input(mut self, input: &str) -> Self {
        self.input = input.bytes().collect();
        self
    }

    pub fn output_string(&self) -> String {
        self.output.iter().copied().map(|x| x as char).collect()
    }

    pub fn output_bytes(&self) -> Vec<u8> {
        self.output.clone()
    }

    pub fn putchar(&mut self, ch: char) {
        self.output.push(ch as u8);
    }

    pub fn putint(&mut self, num: i64) {
        for ch in num.to_string().bytes() {
            self.output.push(ch);
        }
    }

    pub fn putfloat(&mut self, num: f64) {
        for ch in num.to_string().bytes() {
            self.output.push(ch);
        }
    }


    unsafe fn putstr(&mut self, s: *const i8) {
        // Reinterpret the pointer as a string
        if s.is_null() {
            return;
        }
        let cs = unsafe { std::ffi::CStr::from_ptr(s) };
        // Convert to a string
        let cs = cs.to_str().unwrap();

        for ch in cs.bytes() {
            self.output.push(ch);
        }
    }
}

impl Display for TestInterface {
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        /*
        match (String::from_utf8(input), String::from_utf8(output)) {
            (Ok(input), Ok(output)) => write!(f, "Remaining Input: {}\nOutput: {}", input, output),
            (Err(_), Ok(output)) => write!(f, "Remaining Input: {:?}\nOutput: {}", self.input, output),
            (Ok(input), Err(_)) => write!(f, "Remaining Input: {}\nOutput: {:?}", input, self.output),
            (Err(_), Err(_)) => write!(f, "Remaining Input: {:?}\nOutput: {:?}", self.input, self.output),
        }
        */
        write!(f, "{}", String::from_utf8_lossy(&self.output))
    }
}

#[derive(Default)]
pub struct InteractiveInterface;

type BuiltinFn = fn(&mut TestInterface, Vec<i64>) -> i64;

lazy_static! {
    static ref BUILTINS: HashMap<&'static str, BuiltinFn> = {
        let mut map: HashMap<&'static str, BuiltinFn> = HashMap::new();

        map.insert("read", |ti, _args| {
            // Read in exactly one character
            let ch = ti.input.pop_front().unwrap_or(0);
            ch as i64
        });

        map.insert("write", |ti, args| {
            ti.putchar(args[0] as u8 as char);
            0
        });


        map.insert("putc", |ti, args| {
            ti.putchar(args[0] as u8 as char);
            0
        });

        map.insert("puti", |ti, args| {
            ti.putint(args[0]);
            0
        });

        map.insert("putf", |ti, args| {
            ti.putfloat(f64::from_bits(args[0] as u64));
            0
        });


        map.insert("puts", |ti, args| {
            unsafe { ti.putstr(args[0] as *const i8); }
            0
        });
        
        map.insert("putsln", |ti, args| {
            unsafe { ti.putstr(args[0] as *const i8); }
            ti.putchar('\n');
            0
        });

        map.insert("idx", |_ti, args| {
            let ptr = args[0] as *const i64;
            let idx = args[1] as usize;
            unsafe {
                ptr.add(idx) as i64
            }
        });

        map.insert("malloc", |_ti, args| {
            let size = args[0] as usize;
            // Call malloc
            let ptr = Box::into_raw(vec![0; size + 100].into_boxed_slice());
            ptr as *const i64 as i64
        });

        map.insert("free", |_ti, args| {
            let ptr = args[0] as *mut i64;
            let _ = unsafe { Box::from_raw(ptr) };
            0
        });

        map.insert("deref", |_ti, args| {
            let ptr = args[0] as *const i64;
            unsafe {
                *ptr
            }
        });

        map.insert("fadd", |_ti, args| f64::to_bits(f64::from_bits(args[0] as u64) + f64::from_bits(args[1] as u64)) as i64);
        map.insert("fsub", |_ti, args| f64::to_bits(f64::from_bits(args[0] as u64) - f64::from_bits(args[1] as u64)) as i64);
        map.insert("fmul", |_ti, args| f64::to_bits(f64::from_bits(args[0] as u64) * f64::from_bits(args[1] as u64)) as i64);
        map.insert("fdiv", |_ti, args| f64::to_bits(f64::from_bits(args[0] as u64) / f64::from_bits(args[1] as u64)) as i64);
        map.insert("fneg", |_ti, args| f64::to_bits(-f64::from_bits(args[0] as u64)) as i64);
        map.insert("frem", |_ti, args| f64::to_bits(f64::from_bits(args[0] as u64) % f64::from_bits(args[1] as u64)) as i64);

        map.insert("flt", |_ti, args| if f64::from_bits(args[0] as u64) < f64::from_bits(args[1] as u64) { 1 } else { 0 });
        map.insert("lt", |_ti, args| if args[0] < args[1] { 1 } else { 0 });
        map.insert("le", |_ti, args| if args[0] <= args[1] { 1 } else { 0 });

        map.insert("add", |_ti, args| args[0] + args[1]);
        map.insert("sub", |_ti, args| args[0] - args[1]);
        map.insert("div", |_ti, args| args[0] / args[1]);
        map.insert("mul", |_ti, args| args[0] * args[1]);
        map.insert("rem", |_ti, args| args[0] % args[1]);

        map.insert("eq", |_ti, args| if args[0] == args[1] { 1 } else { 0 });
        map.insert("neq", |_ti, args| if args[0] != args[1] { 1 } else { 0 });

        map.insert("round", |_ti, args| f64::to_bits(f64::from_bits(args[0] as u64).round()) as i64);
        map.insert("floor", |_ti, args| f64::to_bits(f64::from_bits(args[0] as u64).floor()) as i64);
        map.insert("ceil", |_ti, args| f64::to_bits(f64::from_bits(args[0] as u64).ceil()) as i64);

        map.insert("to_float", |_ti, args| f64::to_bits(args[0] as f64) as i64);
        map.insert("to_int", |_ti, args| f64::from_bits(args[0] as u64) as i64);
        
        map
    };
}

impl Interface for TestInterface {
    fn has_extern(&self, name: &str) -> bool {
        BUILTINS.contains_key(name)
    }

    fn external_call(&mut self, name: &str, args: Vec<i64>) -> Result<i64> {
        Ok(BUILTINS[name](self, args))
    }
}

// impl Interface for TestInterface {
//     fn has_extern(&self, name: &str) -> bool {
//         match name {
//             "fadd"
//             | "fsub"
//             | "fmul"
//             | "fdiv"
//             | "frem"
//             | "flt"
//             | "add"
//             | "mul"
//             | "div"
//             | "lt"
//             | "eq"
//             | "put"
//             | "putnum"
//             | "fprint"
//             | "to_float"
//             | "to_int"
//             | "round"
//             | "floor"
//             | "ceil"
//             | "deref" => true,

//             _ => false,
//         }
//     }

//     fn external_call(&mut self, name: &str, args: Vec<i64>) -> Result<i64> {
//         Ok(match name {
//             "put" => {
//                 self.output.push(args[0]);
//                 0
//             },
//             "putnum" => {
//                 for ch in args[0].to_string().bytes() {
//                     self.output.push(ch as i64);
//                 }
//                 0
//             },
//             "fprint" => {
//                 for ch in f64::from_bits(args[0] as u64).to_string().bytes() {
//                     self.output.push(ch as i64);
//                 }
//                 0
//             },
//             "fadd" => f64::to_bits(f64::from_bits(args[0] as u64) + f64::from_bits(args[1] as u64)) as i64,
//             "fsub" => f64::to_bits(f64::from_bits(args[0] as u64) - f64::from_bits(args[1] as u64)) as i64,
//             "fmul" => f64::to_bits(f64::from_bits(args[0] as u64) * f64::from_bits(args[1] as u64)) as i64,
//             "fdiv" => f64::to_bits(f64::from_bits(args[0] as u64) / f64::from_bits(args[1] as u64)) as i64,
//             "fneg" => f64::to_bits(-f64::from_bits(args[0] as u64)) as i64,
//             "frem" => f64::to_bits(f64::from_bits(args[0] as u64) % f64::from_bits(args[1] as u64)) as i64,
//             "flt" => if f64::from_bits(args[0] as u64) < f64::from_bits(args[1] as u64) { 1 } else { 0 },
//             "lt" => if args[0] < args[1] { 1 } else { 0 },

//             "eq" => if args[0] == args[1] { 1 } else { 0 },
//             "add" => args[0] + args[1],
//             "sub" => args[0] - args[1],
//             "mul" => args[0] * args[1],
//             "div" => args[0] / args[1],
            
//             "deref" => args[0],
            
//             "round" => f64::to_bits(f64::from_bits(args[0] as u64).round()) as i64,
//             "floor" => f64::to_bits(f64::from_bits(args[0] as u64).floor()) as i64,
//             "ceil" => f64::to_bits(f64::from_bits(args[0] as u64).ceil()) as i64,
            
//             "to_float" => f64::to_bits(args[0] as f64) as i64,
//             "to_int" => f64::from_bits(args[0] as u64) as i64,
//             _ => anyhow::bail!("Unknown external function: {}", name),
//         })
//     }
// }