/*
 * AFL Test Case Example
 * This is a simple program that can be used for fuzz testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
    
    char buffer[1024];
    ssize_t bytes_read;
    
    // Read from stdin (typical for AFL fuzzing)
    bytes_read = read(0, buffer, sizeof(buffer) - 1);
    
    if (bytes_read <= 0) {
        printf("No input received\n");
        return 0;
    }
    
    buffer[bytes_read] = '\0';
    
    // Example processing that could trigger different code paths
    if (bytes_read > 100) {
        printf("Large input detected: %zd bytes\n", bytes_read);
    } else {
        printf("Small input: %s\n", buffer);
    }
    
    // Look for specific patterns that might trigger bugs
    if (strstr(buffer, "CRASH")) {
        // Intentional crash for testing purposes
        int *p = NULL;
        *p = 42;
    }
    
    if (strstr(buffer, "VULN")) {
        // Buffer overflow for testing
        char small_buffer[10];
        strcpy(small_buffer, buffer);  // Potential overflow
        printf("Vulnerable code path: %s\n", small_buffer);
    }
    
    // Normal processing
    printf("Processed input successfully\n");
    
    return 0;
}