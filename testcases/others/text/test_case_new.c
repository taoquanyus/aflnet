/*
  Copyright 2025 New Test Case for AFL All rights reserved.

  New test case for AFL (American Fuzzy Lop) - demonstrates various input processing paths
  ----------------------------------------------------------------------------------------

  This test case has multiple branches to help AFL explore different code paths
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {

  char buffer[256];
  int bytes_read;

  // Read input from stdin
  bytes_read = read(0, buffer, sizeof(buffer) - 1);
  if (bytes_read < 0) {
    perror("read");
    exit(1);
  }
  
  buffer[bytes_read] = '\0';  // Null terminate the buffer

  // Multiple conditional branches for fuzzing
  if (bytes_read == 0) {
    printf("No input received\n");
    exit(0);
  }

  // Check for specific pattern 1
  if (bytes_read >= 5 && strncmp(buffer, "FUZZ!", 5) == 0) {
    printf("Pattern 1 detected: FUZZ!\n");
    
    // Additional processing that creates more branches
    if (bytes_read > 10) {
      printf("Long pattern detected with FUZZ!\n");
      // Intentional vulnerability for fuzzing
      char small[5];
      strncpy(small, buffer, bytes_read);  // Potential overflow
      printf("Processed: %s\n", small);
    } else {
      printf("Short pattern detected with FUZZ!\n");
    }
  }
  // Check for specific pattern 2
  else if (bytes_read >= 3 && strncmp(buffer, "BUG", 3) == 0) {
    printf("Bug pattern detected\n");
    
    if (bytes_read > 8) {
      // Potential crash scenario
      int *ptr = NULL;
      *ptr = 100;  // Null pointer dereference
    } else {
      printf("Safe bug pattern processing\n");
    }
  }
  // Check for numeric processing
  else if (bytes_read >= 1 && buffer[0] >= '0' && buffer[0] <= '9') {
    int num = buffer[0] - '0';
    printf("Numeric input detected: %d\n", num);
    
    // Different behavior based on the number
    switch(num) {
      case 1:
        printf("Processing case 1\n");
        break;
      case 2:
        printf("Processing case 2\n");
        if (bytes_read > 5) {
          printf("Extended case 2 processing\n");
        }
        break;
      case 3:
        printf("Processing case 3\n");
        // Potential integer overflow scenario
        unsigned int val = 0xFFFFFFFF;
        val += num;
        printf("Overflow result: %u\n", val);
        break;
      default:
        printf("Processing default numeric case\n");
        break;
    }
  }
  // Long input processing
  else if (bytes_read > 50) {
    printf("Long input received (%d bytes), processing in chunks\n", bytes_read);
    
    for (int i = 0; i < bytes_read; i++) {
      if (buffer[i] == '\n' || buffer[i] == '\r') {
        printf("Line break detected at position %d\n", i);
        break;
      }
      
      // Check for special characters
      if (buffer[i] == 'A' && i + 4 < bytes_read) {
        if (strncmp(buffer + i, "AFL", 3) == 0) {
          printf("Embedded AFL pattern at position %d\n", i);
          break;
        }
      }
    }
  }
  // Default processing
  else {
    printf("Standard input processing: %.*s\n", bytes_read, buffer);
    
    // Check for palindrome (creates more conditions)
    int is_palindrome = 1;
    for (int i = 0; i < bytes_read / 2; i++) {
      if (buffer[i] != buffer[bytes_read - 1 - i]) {
        is_palindrome = 0;
        break;
      }
    }
    
    if (is_palindrome) {
      printf("Input is a palindrome\n");
    } else {
      printf("Input is not a palindrome\n");
    }
  }

  return 0;
}