use criterion::{black_box, criterion_group, criterion_main, Criterion};
use anyhow::Result;
use std::{fs::File, io::{Read, Write}, path::Path};
use mage::*;
use tracing::warn;

const FFI_TO_LINK: &str = "examples/libexample.c";

// Example function that compiles and runs an .mg file with the LLVM backend:
fn bench_mg_with_c(path: &Path, compile: bool, run: bool) -> Result<()> {
    if compile {
        // 1) Read .mg source
        let mut code = String::new();
        File::open(&path)?.read_to_string(&mut code)?;
    
        // 2) Parse
        let program = parse(&code)?;
    
        // 3) Compile to LLVM IR
        let c_cide = CCompiler::default().compile(program)?;  
        // NOTE: you might have your own `LLVMBackend::new()`, etc. 
        // The key is that we now produce IR as a string.
    
        // 4) Write IR to a .ll file
        let c_path = path.with_extension("c");
        let mut c_file = File::create(&c_path)?;
        write!(c_file, "{}", c_cide)?;
    
        // 5) Use clang (or llc + gcc) to compile the .ll to an executable
        //    e.g. clang -o foo.out foo.ll
        let status = std::process::Command::new("clang")
            .arg(&c_path)
            .arg(FFI_TO_LINK)
            .arg("-O3")
            .arg("-o")
            .arg(path.with_extension("out"))
            .status()?;
    
        assert!(
            status.success(),
            "Failed to compile LLVM IR for {}",
            path.display()
        );
    }

    if run {
        // 6) Run the compiled program
        let mut input_text = String::new();
        let input_file_path = path.with_extension("in.txt");
        if input_file_path.exists() {
            File::open(input_file_path)?.read_to_string(&mut input_text)?;
        } else {
            warn!("No input file found for {}", path.display());
        }
    
        let mut cmd = std::process::Command::new(path.with_extension("out"));
        let mut handle = cmd
            .stdin(std::process::Stdio::piped())
            .stdout(std::process::Stdio::piped())
            .spawn()?;
        handle.stdin.as_mut().unwrap().write_all(input_text.as_bytes())?;
        let output = handle.wait_with_output()?.stdout;
    
        // 7) Check that the output is non-empty
        //    (Then `expected_pass_compiled` compares it to .out.txt)
        assert!(
            !output.is_empty(),
            "No output from {}",
            path.display()
        );
    }

    // Delete the .ll file and the compiled executable
    Ok(())
}

// Criterion will repeatedly call this to measure performance.
fn bench_compilation(c: &mut Criterion) {
    // If you have multiple .mg files under `examples/benchmarks/expected-pass/`,
    // gather them all and measure each individually.
    let mg_files = std::fs::read_dir("examples/benchmarks/")
        .expect("Could not read expected-pass directory")
        .filter_map(|entry| {
            let path = entry.ok()?.path();
            if path.extension()?.to_str()? == "mg" {
                Some(path)
            } else {
                None
            }
        })
        .collect::<Vec<_>>();

    // Bench each file
    for mg_file in mg_files {
        // Create a custom benchmark ID based on the filename
        let test_name = format!("{} (C compilation)", mg_file.file_stem().unwrap().to_string_lossy());

        c.bench_function(&test_name, |b| {
            b.iter(|| {
                // We call `compile_mg_llvm` once per iteration
                // In a real scenario, you might do more steps (link, run, etc.)
                let _ = bench_mg_with_c(black_box(mg_file.as_path()), true, false);
            });
        });
    }
}

// This is a simple benchmark that measures the performance of the `bench_mg_with_llvm` function.
fn bench_runtime(c: &mut Criterion) {
    let mut group = c.benchmark_group("C Execution");
    group.sample_size(10);

    // If you have multiple .mg files under `examples/benchmarks/expected-pass/`,
    // gather them all and measure each individually.
    let mg_files = std::fs::read_dir("examples/benchmarks/")
        .expect("Could not read expected-pass directory")
        .filter_map(|entry| {
            let path = entry.ok()?.path();
            if path.extension()?.to_str()? == "mg" {
                Some(path)
            } else {
                None
            }
        })
        .collect::<Vec<_>>();

    // Bench each file
    for mg_file in mg_files {
        // Create a custom benchmark ID based on the filename
        let test_name = format!("{} (C execution)", mg_file.file_stem().unwrap().to_string_lossy());

        group.bench_function(&test_name, |b| {
            b.iter(|| {
                // We call `compile_mg_llvm` once per iteration
                // In a real scenario, you might do more steps (link, run, etc.)
                let _ = bench_mg_with_c(black_box(mg_file.as_path()), false, true);
            });
        });
    }

    group.finish();
}

//
// Similarly, you could define a bench_expected_fail_c or any other suite
// for different folders or scenarios.
//

// Register benchmarks with Criterion.
// The first argument to `criterion_group!` is the group name, 
// followed by the function(s) that define your benchmarks.
criterion_group!(benches, bench_compilation, bench_runtime);
criterion_main!(benches);