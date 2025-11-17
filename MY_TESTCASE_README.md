# Custom AFL Test Case

This directory contains a custom test case for AFL (American Fuzzy Lop) fuzzing framework.

## Files

- `my_test_case.c` - A custom C program designed for fuzzing with multiple complex code paths
- `my_test_case.mk` - Makefile to compile the test case with AFL instrumentation

## Features of the Test Case

The test case includes several characteristics that make it suitable for fuzzing:

1. **Multiple complex conditional branches** - Different code paths based on various input patterns
2. **Input validation** - Checks for specific patterns, mathematical expressions, and palindromes
3. **Intentional vulnerabilities** - Includes potential buffer overflows for testing
4. **Input processing** - Reads from stdin and processes data in various ways
5. **Mathematical operations** - Processes simple math expressions like "3+4="
6. **Palindrome detection** - Identifies and processes palindromic inputs

## Usage

To compile the test case with AFL instrumentation:

```bash
make -f my_test_case.mk
```

Or directly with AFL compiler:

```bash
afl-gcc -o my_test_case my_test_case.c
```

To run a simple test:

```bash
echo "VULNTEST" | ./my_test_case
echo "3+4=" | ./my_test_case
echo "abcba" | ./my_test_case
```

To use with AFL fuzzer:

```bash
# Create input directory with initial test cases
mkdir input
echo "initial" > input/seed1
echo "VULN" > input/seed2
echo "1+2=" > input/seed3
echo "aba" > input/seed4

# Run AFL fuzzer
afl-fuzz -i input -o output ./my_test_case
```

## Code Paths

The test case has multiple conditional branches that can be triggered by different inputs:

- Inputs starting with "VULN" trigger the vulnerability pattern path
- Inputs matching math format "X+Y=" (e.g., "3+4=") trigger math operation path
- Palindromic inputs (like "abcba") trigger palindrome detection path
- Long inputs (>50 bytes) trigger the long input processing path
- Empty inputs trigger the empty input path
- Other inputs follow the standard processing path

This diversity helps AFL explore different code paths during fuzzing.