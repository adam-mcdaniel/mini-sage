use anyhow::{Context, Result};
use mage::*;
use std::{
    collections::VecDeque, io::{Read, Write}, fmt::{Display, Formatter}, fs::File
};


// Use clap to parse command line arguments
use clap::{Parser, ValueEnum};

#[derive(Debug, Copy, Clone, PartialEq, Eq, PartialOrd, Ord, ValueEnum, Default)]
enum Backend {
    C,
    LLVM,
    #[default]
    Interpreter,
}

#[derive(Parser, Debug)]
#[command(version, about, long_about = None)]
struct Args {
    /// The input file to run or compile
    input_file: String,

    /// The output file to write to
    #[arg(short, long)]
    output_file: Option<String>,

    /// The FFI files to link against
    #[arg(short, long)]
    libraries: Vec<String>,

    /// The backend to use
    #[arg(short, value_enum)]
    target: Option<Backend>,
}

fn main() -> Result<()>{
    let args = Args::parse();
    let input = std::fs::read_to_string(&args.input_file).context("Failed to read input file")?;
    let program = parse(&input).context("Failed to parse input file")?;

    let output = match args.target.unwrap_or(Backend::Interpreter) {
        Backend::C => {
            let mut c = C::new();
            c.compile(program)?
        }
        Backend::LLVM => {
            let mut llvm = LLVMCompiler::new();
            llvm.compile(program)?
        }
        Backend::Interpreter => {
            let i = Interpreter::new(InteractiveInterface::default());
            let _interface = i.run(&program).context("Failed to run program")?;
            "".to_string()
        }
    };

    if [Some(Backend::Interpreter), None].contains(&args.target) {
        return Ok(())
    }

    let path = std::path::Path::new(args.output_file.as_deref().unwrap_or("output")).with_extension(
        match args.target.unwrap() {
            Backend::C => "c",
            Backend::LLVM => "ll",
            Backend::Interpreter => unreachable!(),
        }
    );
    let mut file = File::create(&path)?;
    write!(file, "{}", output)?;

    // Compile the file
    let mut cmd = std::process::Command::new("gcc");
    if args.libraries.iter().any(|lib| lib.ends_with(".c")) {
        cmd
            .arg(&path)
            .args(&args.libraries);
    } else {
        cmd
            .arg(&path);
    }
    let status = cmd.arg("-o")
        .arg(path.with_extension("exe"))
        .status()?;
    if !status.success() {
        return Err(anyhow::anyhow!("Failed to compile {}", path.display()));
    }

    Ok(())
}
