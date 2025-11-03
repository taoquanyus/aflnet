# AFL Test Case Examples

This document provides examples of test cases for use with AFL (American Fuzzy Lop) fuzzing tool.

## Test Case Files

### Text Input Files
- `/workspace/testcases/others/text/sample_input.txt` - A sample text input file with various character types and edge cases

### C Source Files
- `/workspace/test_case_detailed.c` - A sample C program that can be used for fuzz testing with intentional vulnerabilities for testing purposes

## How to Use These Test Cases

### For fuzzing with afl-fuzz:

```bash
# Compile your target program with afl-gcc or afl-clang-fast
afl-gcc -o target_program target.c

# Create an input directory with test cases
mkdir input_dir
cp testcases/others/text/sample_input.txt input_dir/

# Run afl-fuzz
afl-fuzz -i input_dir -o output_dir ./target_program
```

### Example using the sample C file:

```bash
# Compile the sample test case
afl-gcc -o test_case_detailed test_case_detailed.c

# Create input directory
mkdir input_dir
echo "normal input" > input_dir/input1.txt
echo "CRASH" > input_dir/input2.txt
echo "VULN this is a long string that might cause overflow" > input_dir/input3.txt

# Run afl-fuzz
afl-fuzz -i input_dir -o output_dir ./test_case_detailed
```

## Purpose

These test cases are designed to:
- Provide initial seed inputs for fuzzing
- Exercise different code paths in target programs
- Help identify potential vulnerabilities
- Demonstrate how to structure test cases for AFL

## Directory Structure

AFL expects test cases to be organized by file type:
- `testcases/images/` - Image format test cases
- `testcases/archives/` - Archive format test cases  
- `testcases/multimedia/` - Multimedia format test cases
- `testcases/others/` - Other format test cases