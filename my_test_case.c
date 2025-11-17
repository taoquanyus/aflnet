/*
  Copyright 2025 My Test Project All rights reserved.

  Custom test case for AFL (American Fuzzy Lop) - demonstrates various input handling scenarios
  ------------------------------------------------------------------------------------------

  This is a custom test case file with multiple code paths to challenge AFL's path discovery
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

  // Process input with multiple conditional branches
  if (bytes_read == 0) {
    printf("No input received\n");
    exit(0);
  }

  // Check for specific pattern 'VULN' that triggers a vulnerability
  if (bytes_read >= 4 && strncmp(buffer, "VULN", 4) == 0) {
    printf("Vulnerability pattern detected!\n");
    
    // Additional checks to create more complex paths
    if (bytes_read >= 8) {
      char extra[5];
      strncpy(extra, buffer + 4, 4);
      extra[4] = '\0';
      
      if (strcmp(extra, "TEST") == 0) {
        printf("Complex vulnerability path taken!\n");
        // Intentional buffer overflow for testing
        char small[10];
        strcpy(small, buffer);  // This will overflow if buffer is larger than 10 chars
        printf("Overflow attempted: %s\n", small);
      } else {
        printf("Simple vulnerability path taken\n");
      }
    }
  }
  // Check for mathematical operations
  else if (bytes_read >= 4 && buffer[1] == '+' && buffer[3] == '=') {
    if (buffer[0] >= '0' && buffer[0] <= '9' && buffer[2] >= '0' && buffer[2] <= '9') {
      int a = buffer[0] - '0';
      int b = buffer[2] - '0';
      int result = a + b;
      printf("Math operation: %d + %d = %d\n", a, b, result);
      
      // Additional path based on result
      if (result > 10) {
        printf("Large result detected\n");
      } else {
        printf("Small result: %d\n", result);
      }
    }
  }
  // Long input processing
  else if (bytes_read > 50) {
    printf("Processing long input (%d bytes):\n", bytes_read);
    
    // Count different character types
    int digits = 0, letters = 0, special = 0;
    for (int i = 0; i < bytes_read; i++) {
      if (buffer[i] >= '0' && buffer[i] <= '9') digits++;
      else if ((buffer[i] >= 'A' && buffer[i] <= 'Z') || (buffer[i] >= 'a' && buffer[i] <= 'z')) letters++;
      else special++;
    }
    
    printf("Stats - Digits: %d, Letters: %d, Special: %d\n", digits, letters, special);
  }
  // Check for palindrome (only if none of the above conditions match)
  else if (bytes_read > 2) {
    int is_palindrome = 1;
    for (int i = 0; i < bytes_read / 2; i++) {
      if (buffer[i] != buffer[bytes_read - 1 - i]) {
        is_palindrome = 0;
        break;
      }
    }
    
    if (is_palindrome) {
      printf("Palindrome detected: %s\n", buffer);
      
      // Additional vulnerability path in palindrome case
      if (bytes_read > 10) {
        // Potential overflow in palindrome case
        char temp[5];
        strcpy(temp, buffer);  // This will overflow
        printf("Palindrome overflow: %s\n", temp);
      }
    } else {
      printf("Not a palindrome: %s\n", buffer);
    }
  }
  // Default processing
  else {
    printf("Default processing: %s\n", buffer);
  }

  return 0;
}