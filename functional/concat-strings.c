#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUFFER 200

void concatStrings(char* s1, char* s2);
void readInput(char* input);
double getAvg(double* arr, int n);

int main()
{
    /*
        LEARNING LESSON:
            * When using malloc() and realloc() in any way,
              never staticaly allocate memory to the strings.
              Instead, dynamically assign memory with malloc()
              and strcpy().
    */
    
    
    /*
    // ATTEMPT 1 - FAIL:
    char s1[] = "Joel";
    char s2[] = "BletGoat";
    */
    
    // ATTEMPT 2 - SUCCESS
    char* s1 = malloc(sizeof(char) * 10);
    char* s2 = malloc(sizeof(char) * 15);
    
    strcpy(s1, "Joel");
    strcpy(s2, "BletGoat");
    
    
    /*
    // BUILT IN APPROACH:
    strcat(s1, s2); 
    printf("s1: %s\n", s1); // "JoelBletGoat"
    */
    
    
    concatStrings(s1, s2);
    printf("s1: %s, s2: %s\n", s1, s2); // s1 = "JoelBletGoat", s2 = "BletGoat"
    
    
    
    
    // GRADING PROGRAM:
    
    char input[MAXBUFFER];
    readInput(input);
    
    char* token = strtok(input, ", ");
    double* grades = malloc(sizeof(double) * 5);
    double* initPos = grades;
    
    while (token != NULL) {
        *(grades++) = strtod(token, NULL);
        token = strtok(NULL, ", ");
    }
    
    grades = initPos; // Restore initial position

    printf("FINAL AVG: %.2lf\n", getAvg(grades, 5));
    
    
    free(s1);
    free(s2);
    return 0;
}

void concatStrings(char* s1, char* s2) {
    int newLength = strlen(s1) + strlen(s2);
    s1 = realloc(s1, sizeof(char) * newLength);

    int startIdx = strlen(s1);
    for (int i = startIdx; i < newLength; i++) {
        s1[i] = s2[i - startIdx];
    }
}

void readInput(char* input) {
    fgets(input, MAXBUFFER, stdin);
    input[strlen(input) - 1] = '\0';
}

double getAvg(double* arr, int n) {
    double sum = 0;
    int i = -1;
    while (++i < n) {
        sum += *arr;
        *(arr++);
    }
    
    return sum / n;
}