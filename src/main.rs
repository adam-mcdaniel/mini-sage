use anyhow::{Context, Result};
use mage::*;
use std::{
    io::Write, fs::File
};

use tracing::{info, Level};
use tracing_subscriber::FmtSubscriber;

// Use clap to parse command line arguments
use clap::{Parser, ValueEnum};

#[derive(Debug, Copy, Clone, PartialEq, Eq, PartialOrd, Ord, ValueEnum, Default)]
enum Backend {
    C,
    Llvm,
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

    /// Include debug information
    #[arg(short, long)]
    debug: bool,

    /// Compile with release optimizations
    #[arg(long)]
    release: bool,

    /// Compile with address sanitizer
    #[arg(long)]
    asan: bool,
}

fn repl() -> Result<()> {
    use rustyline::error::ReadlineError;
    use rustyline::DefaultEditor;

    // `()` can be used when no completer is required
    let mut rl = DefaultEditor::new()?;

    let mut lines = "".to_string();
    let mut i = Interpreter::new(InteractiveInterface);
    let mut prompt = ">>> ";
    loop {

        let readline = rl.readline(&prompt);
        match readline {
            Ok(line) => {
                rl.add_history_entry(line.as_str())?;

                lines.push_str(&line);

                // Try to parse the line
                let program = parse(&lines);

                match program {
                    Ok(program) => {
                        // Run the program
                        // if let Err(e) = i.partial_run(&program).context("Failed to run program") {
                        //     println!("Error: {:?}", e);
                        // }
                        match i.partial_run(&program) {
                            Ok(_) if !lines.is_empty() || !line.is_empty() => {
                                println!("");
                            }
                            Ok(_) => {}
                            Err(e) => {
                                println!("Error: {:?}", e);
                            }
                        }

                        lines.clear();
                        prompt = ">>> ";
                    }
                    Err(_e) if !line.is_empty() => {
                        prompt = "... ";
                    }
                    Err(e) => {
                        println!("Error: {:?}", e);
                        prompt = ">>> ";
                        lines.clear();
                    }
                }
            },
            Err(ReadlineError::Interrupted) => {
                println!("CTRL-C");
                lines.clear();
                continue
            },
            Err(ReadlineError::Eof) => {
                println!("CTRL-D");
                break
            },
            Err(err) => {
                println!("Error: {:?}", err);
                break
            }
        }
    }

    Ok(())
}

fn main() -> Result<()> {
    // a builder for `FmtSubscriber`.
    let subscriber = FmtSubscriber::builder()
        // all spans/events with a level higher than TRACE (e.g, debug, info, warn, etc.)
        // will be written to stdout.
        .with_max_level(Level::TRACE)
        // completes the builder.
        .finish();
    tracing::subscriber::set_global_default(subscriber)
        .expect("setting default subscriber failed");

    let args = Args::parse();
    
    if args.input_file == "-" {
        return repl();
    }

    let input = std::fs::read_to_string(&args.input_file).context("Failed to read input file")?;
    let program = parse(&input).context("Failed to parse input file")?;

    let output = match args.target.unwrap_or(Backend::Interpreter) {
        Backend::C => {
            let mut c = CCompiler;
            c.compile(program)?
        }
        Backend::Llvm => {
            let mut llvm = LLVMCompiler::default();
            llvm.compile(program)?
        }
        Backend::Interpreter => {
            let i = Interpreter::new(InteractiveInterface);
            let _interface = i.run(&program).context("Failed to run program")?;

            /*
            use std::io::Read;
            let path = std::path::Path::new(&args.input_file);
            let mut input_text = String::new();
            let input_file_path = path.with_extension("in.txt");
            if input_file_path.exists() {
                File::open(input_file_path)?.read_to_string(&mut input_text)?;
            } else {
                tracing::warn!("No input file found for {}", path.display());
            }

            let i = Interpreter::new(TestInterface::default().with_string_input(&input_text));
            let interface = i.run(&program).context("Failed to run program")?;
            println!("{}", interface.output_string());
            */

            "".to_string()
        }
    };

    if [Some(Backend::Interpreter), None].contains(&args.target) {
        return Ok(())
    }

    let path = std::path::Path::new(args.output_file.as_deref().unwrap_or("output")).with_extension(
        match args.target.unwrap() {
            Backend::C => "c",
            Backend::Llvm => "ll",
            Backend::Interpreter => unreachable!(),
        }
    );
    let mut file = File::create(&path)?;
    write!(file, "{}", output)?;

    // Compile the file
    let mut cmd = std::process::Command::new("clang");
    if args.libraries.iter().any(|lib| lib.ends_with(".c")) {
        cmd
            .arg(&path)
            .args(&args.libraries);
    } else {
        cmd
            .arg(&path);
    }
    if args.debug {
        cmd.arg("-g");
        info!("Compiling with debug information");
    }
    if args.release {
        cmd.arg("-O3");
        info!("Compiling with release optimizations");
    }
    if args.asan {
        cmd.arg("-fsanitize=address");
        info!("Compiling with address sanitizer");
    }
    let status = cmd.arg("-o")
        .arg(path.with_extension("exe"))
        .status()?;
    if !status.success() {
        return Err(anyhow::anyhow!("Failed to compile {}", path.display()));
    }

    Ok(())
}
