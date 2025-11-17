# Makefile for my_test_case.c
# This provides targets to compile the custom test case for AFL fuzzing

CC = afl-gcc
CFLAGS = -Wall -g

# Default target
all: my_test_case

# Compile the test case with AFL instrumentation
my_test_case: my_test_case.c
	$(CC) $(CFLAGS) -o my_test_case my_test_case.c

# Alternative compilation with AFL's clang if available
afl-clang: my_test_case.c
	afl-clang-fast -o my_test_case my_test_case.c

# Clean build artifacts
clean:
	rm -f my_test_case

# Phony targets
.PHONY: all clean afl-clang