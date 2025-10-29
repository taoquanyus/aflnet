/*
  Copyright 2025 Test Project All rights reserved.

  Test case for AFL (American Fuzzy Lop) - a simple program to test input handling
  ------------------------------------------------------------------------

  This is a test case file to demonstrate proper test structure for AFL
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {

  char buffer[128];
  int bytes_read;

  // Read input from stdin
  bytes_read = read(0, buffer, sizeof(buffer) - 1);
  if (bytes_read < 0) {
    perror("read");
    exit(1);
  }
  
  buffer[bytes_read] = '\0';  // Null terminate the buffer

  // Simple processing with multiple conditional branches for fuzzing
  if (bytes_read == 0) {
    printf("Empty input received\n");
    exit(0);
  }

  // Check for specific patterns that could trigger different code paths
  if (buffer[0] == 'A' && bytes_read > 4) {
    if (buffer[1] == 'F' && buffer[2] == 'L') {
      printf("AFL pattern detected!\n");
      if (buffer[3] == 'T' && buffer[4] == 'E' && buffer[5] == 'S' && buffer[6] == 'T') {
        printf("Extended AFLTEST pattern found!\n");
        // Intentional vulnerability for fuzzing - buffer overflow possibility
        char small_buffer[10];
        strcpy(small_buffer, buffer);  // Potential overflow for testing
        printf("Copied: %s\n", small_buffer);
      }
    }
  } else if (buffer[0] == 'B' && bytes_read > 2) {
    if (buffer[1] == 'U' && buffer[2] == 'G') {
      printf("BUG pattern detected - potential crash scenario!\n");
      // Cause a potential crash for testing
      if (bytes_read > 10) {
        int *null_ptr = NULL;
        *null_ptr = 42;  // Dereference null pointer for testing
      }
    }
  } else if (bytes_read > 20) {
    printf("Long input detected: %d bytes\n", bytes_read);
    // Process longer input differently
    for (int i = 0; i < bytes_read && i < 20; i++) {
      if (buffer[i] >= '0' && buffer[i] <= '9') {
        printf("Digit found at position %d: %c\n", i, buffer[i]);
      }
    }
  } else {
    printf("Standard input processed: %s\n", buffer);
  }

  return 0;
}