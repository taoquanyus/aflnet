# New AFL Test Case

This directory contains a new sample test case for AFL (American Fuzzy Lop) fuzzing framework.

## Files

- `test_case_new.c` - A new C program designed for fuzzing with multiple code paths
- `test_case_new.mk` - Makefile to compile the test case

## Features of the Test Case

The test case includes several characteristics that make it suitable for fuzzing:

1. **Multiple conditional branches** - Different code paths based on input patterns
2. **Pattern matching** - Recognizes specific patterns like "FUZZ!" and "BUG"
3. **Intentional vulnerabilities** - Includes potential buffer overflow and null pointer dereference for testing
4. **Numeric processing** - Handles numeric inputs with different behaviors
5. **Long input processing** - Processes inputs longer than 50 bytes differently
6. **Palindrome detection** - Additional processing that creates more conditional branches

## Input Patterns

The test case has multiple conditional branches that can be triggered by different inputs:

- **Empty input** - Triggers the empty input path
- **Inputs starting with "FUZZ!"** - Triggers extended pattern processing (short vs long)
- **Inputs starting with "BUG" and length > 8** - Triggers potential crash scenario
- **Numeric inputs (0-9)** - Triggers numeric processing with different cases
- **Long inputs (>50 bytes)** - Triggers chunked processing and line break detection
- **Other inputs** - Follows standard processing with palindrome detection

## Usage

To compile the test case:
```bash
gcc -Wall -g -o test_case_new test_case_new.c
```

To run a simple test:
```bash
echo "FUZZ! test input" | ./test_case_new
echo "BUG crash test" | ./test_case_new
echo "12345" | ./test_case_new
```

## Using with AFL

To compile with AFL instrumentation, first build AFL if available, then:
```bash
afl-gcc -Wall -g -o test_case_new test_case_new.c
```

To use with AFL fuzzer:
```bash
# Create input directory with initial test cases
mkdir -p input
echo "initial" > input/seed1
echo "FUZZ!" > input/seed2
echo "123" > input/seed3

# Run AFL fuzzer
afl-fuzz -i input -o output ./test_case_new
```

## Code Coverage

This test case is designed to help AFL explore different execution paths:
- Path 1: Empty input handling
- Path 2: "FUZZ!" pattern with short input
- Path 3: "FUZZ!" pattern with long input (potential overflow)
- Path 4: "BUG" pattern with safe processing
- Path 5: "BUG" pattern with crash scenario
- Path 6: Numeric input processing with different cases
- Path 7: Long input processing with special character detection
- Path 8: Standard input processing with palindrome detection

These diverse paths help AFL maximize code coverage during fuzzing.