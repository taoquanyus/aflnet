# Makefile for test_case_new.c
# This provides targets to compile the new test case for AFL fuzzing

CC = afl-gcc
CFLAGS = -Wall -g

# Default target
all: test_case_new

# Compile the test case with AFL instrumentation
test_case_new: test_case_new.c
	$(CC) $(CFLAGS) -o test_case_new test_case_new.c

# Alternative target with different name
test_new: test_case_new.c
	$(CC) $(CFLAGS) -o test_new test_case_new.c

# Clean build artifacts
clean:
	rm -f test_case_new test_new

# Phony targets
.PHONY: all clean test_new