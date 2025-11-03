/*
  Sample target program for AFL fuzzing
  -------------------------------------
  
  This is a simple program designed to demonstrate AFL fuzzing capabilities.
  It reads input from stdin and processes it in various ways to trigger
  different execution paths that AFL can explore.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
  
  char buffer[256];
  int bytes_read;
  
  // Read up to 255 bytes from stdin (leaving space for null terminator)
  bytes_read = fread(buffer, 1, sizeof(buffer) - 1, stdin);
  if (bytes_read <= 0) {
    fprintf(stderr, "Error reading input\n");
    return 1;
  }
  
  buffer[bytes_read] = '\0';  // Null terminate the buffer
  
  // Process the input in different ways to create multiple execution paths
  
  // Path 1: Check for specific header
  if (bytes_read >= 5 && strncmp(buffer, "AFLFT", 5) == 0) {
    printf("Found AFL header\n");
    
    // Path 2: Additional check after header
    if (bytes_read > 10 && buffer[5] == 'X') {
      printf("Extended AFL header detected\n");
      
      // Path 3: Potential vulnerability for testing
      if (bytes_read > 20) {
        char temp[16];
        strcpy(temp, buffer);  // Potential buffer overflow for AFL to detect
        printf("Copied to temp: %s\n", temp);
      }
    }
  }
  // Path 4: Check for numeric patterns
  else if (bytes_read >= 3 && buffer[0] >= '0' && buffer[0] <= '9') {
    int num = buffer[0] - '0';
    printf("Found digit: %d\n", num);
    
    // Path 5: Different processing based on digit
    if (num > 5) {
      printf("Large digit detected\n");
      // Do some additional processing
      for (int i = 1; i < bytes_read && i < 10; i++) {
        if (buffer[i] == 'X') {
          printf("Found X after large digit\n");
          break;
        }
      }
    } else {
      printf("Small digit detected\n");
    }
  }
  // Path 6: Check for specific keywords
  else if (strstr(buffer, "FUZZ") != NULL) {
    printf("FUZZ keyword found\n");
    
    // Path 7: Additional check for fuzzing
    if (bytes_read > 8) {
      printf("Long FUZZ input\n");
    }
  }
  // Path 8: Default processing
  else {
    printf("Standard input: %.*s\n", bytes_read > 50 ? 50 : bytes_read, buffer);
  }
  
  return 0;
}