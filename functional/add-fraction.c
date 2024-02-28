#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define BUFFERMAX 200

long gcd(long a, long b);
void readInput(char* s);
void addFraction(long nom1, long den1, long nom2, long den2);
long* simplifyFraction(long finalNom, long finalDen);

int main()
{
    char input[BUFFERMAX];
    readInput(input);
    
    // Returns first token
    char* token = strtok(input, ", "); // Splits for cases ", ", "," and " "
    
    long fraction1[2];
    long fraction2[2];
    
    int i = -1;
    while (token != NULL && ++i < 4) {
        
        long current = strtol(token, NULL, 10);
        token = strtok(NULL, ", ");
        
        if (i <= 1) {
            fraction1[i] = current;
        } else {
            fraction2[i - 2] = current;
        }
    }
    
    // printf("%ld / %ld, %ld / %ld\n", fraction1[0], fraction1[1], fraction2[0], fraction2[1]);
    addFraction(fraction1[0], fraction1[1], fraction2[0], fraction2[1]);
    
    return 0;
}

// TODO: Make this return char* and implement to versions: Concatination and substring-insertion
void addFraction(long nom1, long den1, long nom2, long den2) { // Returns a string of the added fraction
    long denomGreatestDivisor = gcd(den1, den2);
    
    long newMergedDen = (den1 * den2) / denomGreatestDivisor;
    
    long multiplicationFactor1 = newMergedDen / den1;
    long multiplicationFactor2 = newMergedDen / den2;
    
    long newMergedNom = (nom1 * multiplicationFactor1) + (nom2 * multiplicationFactor2);
    
    long* finalFraction = malloc(sizeof(long) * 2);
    finalFraction = simplifyFraction(newMergedNom, newMergedDen);
    
    printf("%ld / %ld\n", finalFraction[0], finalFraction[1]);
}


// Function to return gcd of a and b 
long gcd(long a, long b) { 
    // Find Minimum of a and b 
    int result = ((a < b) ? a : b); // The first possibility, is when the gcd is equal to the smallest number of a and b
    while (result > 0) { 
        // Check if both a and b are divisible by result 
        if (a % result == 0 && b % result == 0) { 
            break; 
        } 
        result--; // The current attempt was not divisible by both a and b, decrease the variable and try again
    } 
    // return gcd of a nd b 
    return result; 
}

// Divide by the greastest common divisor in both numbers to preserve their mathematical relation
long* simplifyFraction(long finalNom, long finalDen) {
    long greastestDivisor = gcd(finalNom, finalDen);
    
    long* output = malloc(sizeof(long) * 2);
    output[0] = finalNom / greastestDivisor;
    output[1] = finalDen / greastestDivisor;
    
    return output;
}


void readInput(char* s) {
    fgets(s, BUFFERMAX, stdin);
    s[strlen(s) - 1] = '\0';
}