#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printNChars(char c, int n);

int main()
{
    // char s[] = "Cisbest";
    
    char s[] = "Goatedblets";
    int currentSideLength = strlen(s) - 1;
    int currentMidLength = 0; // += 2 for each iteration
    
    for (int i = 0; i < strlen(s); i++) {
        // char currentRow[(strlen(s) * 2) - 1];
        
        printNChars(' ', currentSideLength); // Left spaces
        
        if (i > 0) {
            printf("%c", s[i]); // Mid character 1
        
            printNChars(' ', currentMidLength); // Mid Spaces
        
            printf("%c", s[i]); // Mid character 2
            
        } else {
            printf("%c", s[i]);
        }
        

        printNChars(' ', currentSideLength); // Right spaces
        
        currentSideLength -= 1;
        
        if (i == 0) {
            currentMidLength += 1;
        } else {
            currentMidLength += 2;
        }
        
        printf("\n");
    }
    
    
    int rowLength = (strlen(s) * 2) - 1;
    int n = strlen(s) - 1;
    for (int i = 0; i < rowLength; i++) {
        
        if (i < (n + 1)) {
            printf("%c", s[n - i]);
        } else {
            printf("%c", s[i - n]);
        }
    }
    
    printf("\n");
    return 0;
}


void printNChars(char c, int n) {
    for (int i = 0; i < n; i++) {
        printf("%c", c);
    }
}


/*
char* appendNCharacters(char c, int n) {
    
}
*/