#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAXBUFFER 200

void readInput(char* s);
long* multiplyFractions(long nom1, long den1, long nom2, long den2);
long gcd(long a, long b);
void simplifyFractions(long* finalOutput);

int main()
{
    char input[MAXBUFFER];
    readInput(input);
    
    char* token = strtok(input, ", "); // strtok(s, delim)
    
    long fractions[4];
    int i = -1;
    while (token != NULL && ++i < 4) {
        long current = strtol(token, NULL, 10);
        fractions[i] = current;
        token = strtok(NULL, ", ");
    }
    
    
    long* multipliedFraction = malloc(sizeof(long) * 2);
    multipliedFraction = multiplyFractions(fractions[0], fractions[1], fractions[2], fractions[3]);
    
    simplifyFractions(multipliedFraction);
    
    printf("%ld / %ld\n", multipliedFraction[0], multipliedFraction[1]);
    
    return 0;
}

long* multiplyFractions(long nom1, long den1, long nom2, long den2) {
    long* output = malloc(sizeof(long) * 2);
    output[0] = nom1 * nom2;
    output[1] = den1 * den2;
    return output;
}


void simplifyFractions(long* finalOutput) {
    long greatestDivisor = gcd(finalOutput[0], finalOutput[1]);
    finalOutput[0] /= greatestDivisor;
    finalOutput[1] /= greatestDivisor;
}


long gcd(long a, long b) {
    long output = a < b ? a : b;
    
    while (output > 0) {
        if (a % output == 0 && b % output == 0) { // If both are divisible by the current factor 'output'
            return output;
        }
        
        output--;
    }
    
    return -1;
}


void readInput(char* s) {
    fgets(s, MAXBUFFER, stdin);
    s[strlen(s) - 1] = '\0';
}
