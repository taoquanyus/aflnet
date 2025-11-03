# AFL Test Input Samples

This directory contains sample input files designed to test the AFL fuzzing capabilities with the sample target program (`sample_fuzz_target.c`).

## Input Files Description

- `input1_afl_header`: Contains the string "AFLFTXTEST123" to trigger the header detection path in the target program.
- `input2_digit_start`: Contains "7XTEST" to trigger the numeric processing path (digit > 5 with 'X' following).
- `input3_fuzz_keyword`: Contains "FUZZINGTEST" to trigger the keyword detection path.
- `input4_normal`: Contains "NORMAL INPUT DATA" as a standard input that follows the default processing path.

## Usage with AFL

To use these test cases with AFL fuzzing:

```bash
# First compile the target with AFL instrumentation
afl-gcc -o sample_fuzz_target sample_fuzz_target.c

# Create output directory for AFL
mkdir afl_output

# Run AFL with these inputs as seeds
afl-fuzz -i test_input_samples -o afl_output ./sample_fuzz_target
```

## Target Program Behavior

The sample target program has multiple execution paths to demonstrate AFL's path exploration capabilities:

1. Header detection: Looks for "AFLFT" at the beginning
2. Numeric processing: Handles inputs starting with digits
3. Keyword detection: Looks for "FUZZ" anywhere in the input
4. Default processing: Handles other inputs

Each path has sub-branches to create a rich exploration space for AFL.