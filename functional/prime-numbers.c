#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool isPrimeNumber(int num);

int main()
{
    printf("Starting program..\n");
    
    /*
    // ERROR: char* = int*. FIX: Cast 'x' to (char*)
    char* p;
    int* x;
    p = x; // Cast here
    */
    
    /*
    // TODO: Test
    char* p;
    char x[]; // No length defined
    p = &x;
    */
    
    /*
    // ERROR: Assigning char* p with address of another pointer (char* = char** --> ERROR)
    char* p;
    char x[10];
    p = &x;
    */
    
    
    // Works:
    /*
    char* p;
    char x[10];
    p = x; // Works: char* = char*

    
    int gg = 65;
    int gg2 = 68;
    */
    
    /*
        NOTE: (%p printing)
            * When pritning regular variables, add '&' sign in front them
            * Don't dereference the pointers/arrays
    */
    // printf("Addresses: %p, %p, %p, %p\n", &gg, &gg2, p, p + 1);
    
    /*
        NOTE: (%d printing)
            * When printing arrays, the altering of the address, as always is
              located inside the paranthesis. The address must also always be
              derefenced outside the paranthesis.
    */
    // printf("Numbers: %d, %d, %d, %d\n", gg, gg2, *p, *(p + 1));
    
    /*
    // WORKS: Pointer variable is assigned as the address of the regular variable
    char* p2;
    char x2;
    p2 = &x2;
    */
    
    printf("Execution continues..\n");
    
    
    // Prime Number Tests:
    printf("%s\n", isPrimeNumber(3) ? "True" : "False"); // T
    printf("%s\n", isPrimeNumber(4) ? "True" : "False");
    printf("%s\n", isPrimeNumber(5) ? "True" : "False"); // T
    printf("%s\n", isPrimeNumber(6) ? "True" : "False");
    printf("%s\n", isPrimeNumber(7) ? "True" : "False"); // T
    printf("%s\n", isPrimeNumber(10) ? "True" : "False");
    printf("%s\n", isPrimeNumber(11) ? "True" : "False"); // T

    return 0;
}

bool isPrimeNumber(int num) {
    int upperLimit = num / 2;
    for (int i = 2; i <= upperLimit; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    
    return true;
}
