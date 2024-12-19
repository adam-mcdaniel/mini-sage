use std::{
    fs::File, io::{Read, Write}, path::Path
};
use anyhow::Result;
use mage::*;


fn expected_pass_compiled(compile_and_run: fn(path: &Path) -> Result<Vec<u8>>) -> Result<()> {
    // Get all the files in the examples/expected-pass directory with the .mg extension
    let files = std::fs::read_dir("examples/expected-pass")?
        .filter_map(|entry| {
            let entry = entry.ok()?;
            let path = entry.path();
            if path.extension()?.to_str()? == "mg" {
                Some(path)
            } else {
                None
            }
        })
        .collect::<Vec<_>>();

    // For each file, compile it and check if it passes
    for file in files {
        // let mut file = File::open(file)?;
        // let mut code = String::new();
        // File::open(&file)?.read_to_string(&mut code)?;

        // let program = mage::parse(&code)?;
        // write!(output, "#include <stdint.h>\nint64_t as_int(double x) {{ return *(int64_t*)&x; }}\ndouble as_float(int64_t x) {{ return *(double*)&x; }}\n\n#if __has_include(\"ffi.h\")\n#include \"ffi.h\"\n#endif\nint main() {{ {} }}", target.compile_stmt(&program, &env)?)?;
        // write!(output, "{}", target.compile(program)?)?;

        let output_bytes = compile_and_run(file.as_path())?;

        // Check if the output is correct
        let mut expected = File::open(file.with_extension("out.txt"))?;
        let mut expected_bytes = Vec::new();
        expected.read_to_end(&mut expected_bytes)?;

        assert_eq!(output_bytes, expected_bytes, "Output from {} does not match expected:\n\n`{}`\n!=\n`{}`", file.display(), String::from_utf8_lossy(&output_bytes), String::from_utf8_lossy(&expected_bytes));
    }

    Ok(())
}

#[test]
fn test_expected_pass_c_backend() -> Result<()> {
    expected_pass_compiled(
        |path| {
            let mut code = String::new();
            File::open(&path)?.read_to_string(&mut code)?;
    
            let program = mage::parse(&code)?;
            let mut output_file = File::create(path.with_extension("c"))?;
            // write!(output_file, "#include <stdint.h>\nint64_t as_int(double x) {{ return *(int64_t*)&x; }}\ndouble as_float(int64_t x) {{ return *(double*)&x; }}\n\n#if __has_include(\"ffi.h\")\n#include \"ffi.h\"\n#endif\nint main() {{ {} }}", target.compile_stmt(&program, &env)?)?;
            write!(output_file, "{}", C.compile(program)?)?;
    
            // Compile the file
            let mut cmd = std::process::Command::new("gcc");
            if path.with_file_name("ffi.c").exists() {
                cmd
                    .arg(path.with_extension("c"))
                    .arg(path.with_file_name("ffi.c"));
            } else {
                cmd
                    .arg(path.with_extension("c"));
            }
            let status = cmd.arg("-o")
                .arg(path.with_extension("out"))
                .status()?;
    
            // Check if the compilation was successful
            assert!(status.success(), "Failed to compile {}", path.display());
    
            // Read the input file
            let mut input_text = String::new();
            let input_file_path = path.with_extension("in.txt");
            if input_file_path.exists() {
                File::open(input_file_path)?.read_to_string(&mut input_text)?;
            }
    
            // Run the compiled file (with the input text as stdin) and get the output
            let mut cmd = std::process::Command::new(path.with_extension("out"));
            let mut handle = cmd.stdin(std::process::Stdio::piped())
                .stdout(std::process::Stdio::piped())
                .spawn()?;
            handle.stdin.as_mut().unwrap().write_all(input_text.as_bytes())?;
            let output = handle.wait_with_output()?.stdout;
    
            assert!(output.len() > 0, "No output from {}", path.display());
            
            // Ok(String::from_utf8_lossy(&output).to_string())
            Ok(output)
        }
    )
}