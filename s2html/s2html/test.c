#include <stdio.h>

// Macro
#define PI 3.14

// Function prototype
void greet();

int main() {
    int value = 42;
    char ch = 'A';
    const char* msg = "Done!";

    // Print statements
    printf("Value: %d\n", value);
    printf("Char: %c\n", ch);
    printf("Message: %s\n", msg);

    greet(); // Call function

    return 0;
}

// Definition
void greet() {
    printf("Hello from greet!\n");
}
