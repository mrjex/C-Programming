#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

// time.h is needed for srand()
#include <time.h> // Time library: Used to access time-related data. In this file, it is utilized as a way of generating a unique random seed


#define MAXVAL 100
#define MINVAL 80

struct q {
    int value;
    struct q* next;
} typedef Node;


// Prototypes:
int randomizeValue();

void printLinkedList(Node** root);
void deAllocateMemory(Node** root);

void insertNodesFirst(Node** root, int n);
void insertNodesLast(Node** root, int n);
void reverseList(Node** root);

Node* currentIterator = NULL;
Node* top = NULL;

/*
    TODO after exams:
        * Fix minor bug: Assigning elements in the transitions with 'insertNodesFirst' and 'insertNodesLast' is not completely synced
        * Github repo TODO: Create arrays 'sequences[]' containing the quantities to add first, last and mid
*/

int main()
{
    srand(time(0)); // LEARNING LESSON: Always put srand(time(0)) in main method
    
    // Insert root
    Node* root = malloc(sizeof(Node));
    root->next = NULL; // Insert first element in entire list
    root->value = randomizeValue();
    
    printf("\n");
    printf("Insert 5 nodes First:\n");
    insertNodesFirst(&root, 5); // Insert 5 elements
    printLinkedList(&root);
    
    
    printf("\n");
    printf("Insert 5 nodes Last:\n");
    insertNodesLast(&root, 5);
    printLinkedList(&root);
    
    
    printf("\n");
    printf("Reverse List:\n");
    reverseList(&root);
    printf("A\n");
    printLinkedList(&root);
    printf("B\n");
    
    deAllocateMemory(&root);
    
    free(root);
    return 0;
}


void printLinkedList(Node** root) {
    currentIterator = *root;
    
    while (currentIterator->next != NULL) {
        printf("Current Element: %d\n", currentIterator->value);
        currentIterator = currentIterator->next;
    }
}

void deAllocateMemory(Node** root) {
    currentIterator = *root;
    
    while (currentIterator->next != NULL) {
        *root = currentIterator->next;
        currentIterator = currentIterator->next;
        free(currentIterator);
    }
}

// Insert randomized nodes
void insertNodesFirst(Node** root, int n) {
    
    currentIterator = *root;
    
    for (int i = 0; i < n; i++) {
        Node* newNode = malloc(sizeof(Node));
        newNode->value = randomizeValue();
        
        // printf("Assigned element: %d\n", newNode->value);
        
        newNode->next = currentIterator;
        
        // currentIterator = currentIterator->prev; If doubly linked list
        currentIterator = newNode; // Move pointer one step backwards (since we connected newNode's next to the previously created nodes) with a singly linked list
    }
    
    *root = currentIterator; // IMPORTANT LINE: Assign value obtained in current iterator to the main variable
}

void insertNodesLast(Node** root, int n) {
    currentIterator = *root; // Iterator node
    
    // Two versions:
    // Node* top = *root; // IMPORTANT NOTE: These 2 lines are essential to restore address to initial node
    top = *root; // Declared globally
    /*
        In essence, we are setting a brand new variable (a local one) to the main one. This tells the
        compiler that the root's current value must remain the same, even after it's peer-variable
        (currentIterator) changes pointer positions.
    */
    
    // Traverse to latest element in the linked list
    while (currentIterator->next != NULL) {
        currentIterator = currentIterator->next;
    }
    
    // currentIterator now points to the position of the latst element
    // printf("Current element (last one): %d\n", currentIterator->value);
    
    for (int i = 0; i < n; i++) {
        Node* newNode = malloc(sizeof(Node));
        newNode->value = randomizeValue();
        
        // printf("New elem: %d\n", newNode->value);
        
        currentIterator->next = newNode;
        newNode->next = NULL;
        
        currentIterator = currentIterator->next;
    }
}

void deleteFirst() { // TODO later
    
}

void deleteLast() { // TODO later
    
}

// Delete element that another element is pointer to, that also points to another element
void deleteMidElement(int i) { // TODO later
    
    /*
        1) Iterate to the previous element of the specified one (i - 1)th, and store this node as 'nodePrev'
        2) Iterate to the specified element ith and call it 'currentNode'
        3) Read the next node as 'nodeNext' by doing 'currentNode->next'
        4) Set 'currentNode' to NULL
        5) Set 'nodePrev->next' to 'nodeNext'
        
        6 - IF Doubly Linked List) Set 'nodeNext.prev' to 'nodePrev'
    */
}

void reverseList(Node** root) {
    Node* prev = NULL;
    Node* curr = *root;
    
    while (curr != NULL) {
        Node* next = curr->next;
        
        curr->next = prev;
        
        prev = curr;
        curr = next;
    }
    
    *root = prev;
}

// Returns randomized value ranging between 'min' and 'max'
int randomizeValue() {
    int num = (rand() % (MAXVAL - MINVAL + 1)) + MINVAL; 
    return num;
}