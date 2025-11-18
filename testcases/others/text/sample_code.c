#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char buffer[100];
    
    if (argc > 1) {
        strncpy(buffer, argv[1], sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0';
        printf("Input: %s\n", buffer);
    } else {
        strcpy(buffer, "default");
        printf("Using default value: %s\n", buffer);
    }
    
    // Test some basic operations
    int len = strlen(buffer);
    printf("Length: %d\n", len);
    
    return 0;
}