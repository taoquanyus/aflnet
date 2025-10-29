# Makefile for test_case_example.c
# This provides targets to compile the test case for AFL fuzzing

CC = afl-gcc
CFLAGS = -Wall -g

# Default target
all: test_case_example

# Compile the test case with AFL instrumentation
test_case_example: test_case_example.c
	$(CC) $(CFLAGS) -o test_case_example test_case_example.c

# Clean build artifacts
clean:
	rm -f test_case_example

# Phony targets
.PHONY: all clean