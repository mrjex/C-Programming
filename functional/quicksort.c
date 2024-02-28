#include <stdio.h>
#include <stdlib.h>


void foo(int *A, int len);


int main(int argc, char* argv[]) {
    
    int myArr[] = {8, 5, 4, 9, 2, 96, 93};
    int arrLenth = sizeof(myArr) / sizeof(int);
    
    // int size = 4 bytes
    // char size: 1 byte
    
    // printf("Size: %lu, %lu\n", sizeof(int), sizeof(myArr) / sizeof(int)); // 4, 7
    
    foo(myArr, arrLenth);
    
    printf("Sorted array:\n");
    for (int i = 0; i < arrLenth; i++) {
        printf("%d ", *(myArr + i));
    }
    
    return 0;
}


void foo(int *A, int len) { // Quicksort
    if (len < 2) return;
    int pivot = A[len / 2];
    int i, j;
    
    for (i = 0, j = len - 1; ; i++, j--) {
        while (A[i] < pivot) i++;
        while (A[j] > pivot) j--;
        if (i >= j) break;
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }
    
    foo(A, i);
    foo(A + i, len - i);
}