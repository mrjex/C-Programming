#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXBUFFER 200


void clearBuffer();
char* binaryInsert(char* sortedS, char targetChar, int right);
bool stringsEqual(char* s, char* s2);
char* getSubstring(char* s, int pos, int length);
char* substringInsertion(char* s, char* substring, int pos);
char* charToStr(char character);
bool isAnagram(char* s1, char* s2);


// TODO: Research Anagram Solution on Geeks For Geeks and compare efficiency and simplicity versus my solution
// TODO: Speedrun implement bubble and selection sort solutions

/*
    2 possible solutions:
        * Binary insertion sort compare output
        * Bubble/Selection sort compare output
*/

int main()
{
    char s1[MAXBUFFER];
    char s2[MAXBUFFER];
    
    printf("First string: ");
    scanf("%s", s1);
    
    printf("Second string: ");
    scanf("%s", s2);
    
    printf("Strings are an anagram: %s\n", isAnagram(s1, s2) ? "True" : "False");
    
    
    clearBuffer();
    return 0;
}


bool isAnagram(char* s1, char* s2) {
    if (strlen(s1) != strlen(s2)) {
        return false;
    }
    
    int commonLength = strlen(s1);
    
    char* sortedS1 = malloc(sizeof(char) * commonLength);
    char* sortedS2 = malloc(sizeof(char) * commonLength);
    
    for (int i = 0; i < commonLength; i++) {
        sortedS1 = binaryInsert(sortedS1, s1[i], i);
        sortedS2 = binaryInsert(sortedS2, s2[i], i);
        // Print here
    }
    
    return stringsEqual(sortedS1, sortedS2);
}

bool stringsEqual(char* s1, char* s2) {
    if (strlen(s1) != strlen(s2)) {
        return false;
    }
    
    for (int i = 0; i < strlen(s1); i++) {
        if (s1[i] != s2[i]) {
            return false;
        }
    }
    
    return true;
}

char* binaryInsert(char* sortedS, char targetChar, int right) {
    int left = 0;
    int mid;
    
    while (left <= right) {
        mid = (left + right) / 2;
        
        if (sortedS[mid] < targetChar) {
            left = mid + 1;
        } else if (sortedS[mid] > targetChar) {
            right = mid - 1;
        } else {
            // Insert, or concatinate 'targetChar' into 'sortedS' at index 'mid'
            sortedS = substringInsertion(sortedS, charToStr(targetChar), mid);
            break;
        }
    }
    
    if (left > right) { // If no matches found in binary search above, insert at current pos
        sortedS = substringInsertion(sortedS, charToStr(targetChar), left);
    }
    
    return sortedS;
}

char* substringInsertion(char* s, char* substring, int pos) {
    char* sFirst = getSubstring(s, 0, (pos + 1));
    char* sLast = getSubstring(s, pos, strlen(s) - pos + 1);
    
    char* output = malloc(sizeof(char) * (strlen(s) + strlen(substring)));
    strcat(output, sFirst);
    strcat(output, substring);
    strcat(output, sLast);
    
    free(sFirst);
    free(sLast);
    
    return output;
}

char* getSubstring(char* s, int pos, int length) {
    char* substring = malloc(sizeof(char) * length);
    
    int endIdx = pos + length;
    for (int i = pos; i < endIdx; i++) {
        substring[i - pos] = *(s + i);
    }
    
    *(substring + length - 1) = '\0';
    return substring;
}

// TODO: Try with int* and add +1 to pointer and see what happens --> Pointer traversal with respect to datatype size



char* charToStr(char character) {
    char* str = malloc(sizeof(char) * 2);
    str[0] = character;
    str[1] = '\0';
    return str;
}


void clearBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF) {};
}