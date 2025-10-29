# AFL Test Case Example

This directory contains a sample test case for AFL (American Fuzzy Lop) fuzzing framework.

## Files

- `test_case_example.c` - A sample C program designed for fuzzing with multiple code paths
- `test_case_example.mk` - Makefile to compile the test case with AFL instrumentation

## Features of the Test Case

The test case includes several characteristics that make it suitable for fuzzing:

1. **Multiple conditional branches** - Different code paths based on input patterns
2. **Input validation** - Checks for specific patterns and lengths
3. **Intentional vulnerabilities** - Includes potential buffer overflow and null pointer dereference for testing
4. **Input processing** - Reads from stdin and processes data in various ways

## Usage

To compile the test case with AFL instrumentation:

```bash
make -f test_case_example.mk
```

Or directly with AFL compiler:

```bash
afl-gcc -o test_case_example test_case_example.c
```

To run a simple test:

```bash
echo "AFLTEST input" | ./test_case_example
```

To use with AFL fuzzer:

```bash
# Create input directory with initial test cases
mkdir input
echo "initial" > input/seed

# Run AFL fuzzer
afl-fuzz -i input -o output ./test_case_example
```

## Code Paths

The test case has multiple conditional branches that can be triggered by different inputs:

- Inputs starting with "AFLTEST" trigger the extended pattern path
- Inputs starting with "BUG" trigger the bug pattern path
- Long inputs (>20 bytes) trigger the long input processing path
- Empty inputs trigger the empty input path
- Other inputs follow the standard processing path

This diversity helps AFL explore different code paths during fuzzing.