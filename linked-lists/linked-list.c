#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// structure describing one node of the list
struct node {
  int data;
  int key;
  struct node* next;
};
// pointing to the beginning of the list and the current node
struct node* head = NULL;
struct node* current = NULL;


void insertFirst(int key, int data);
struct node* deleteFirst();
void printList();

int getLength();
void deleteAll();

int getLength() {
  current = head;
  int count = 0;
  
  while (current->next != current) {
      count++;
      current = current->next;
  }
  
  count++; // Count the element that was neglected due to relational logic between the node-pointers (head points to itself and .next doesn't point to NULL)
  
  return count;
}
// insert link at the first location
void insertFirst(int key, int data) {
  // create a link
  struct node* link = (struct node*)malloc(sizeof(struct node));
  link->key = key;
  link->data = data;
  if (head == NULL) {
    head = link;
    head->next = head;
  } else {
    // point it to old first node
    link->next = head;
    // point first to new first node
    head = link;
  }
}

// delete first item
struct node* deleteFirst() {
  // save reference to first link
  struct node* tempLink = head;
  if (head->next == head) { // If the list only has 1 node (the head) at the moment
    head = NULL;
    return tempLink;
  }
  // mark next to first link as first
  head = head->next;
  // return the deleted link
  return tempLink;
}

void deleteAll() {
    current = head;
    
    while (current->next != current) {
        deleteFirst();
        current = current->next;
    }
    
    deleteFirst();
}


// display the list
void printList() {
  struct node* ptr = head;
  
  printf("\n[ ");
  // start from the beginning
  if (head != NULL) {
     printf("C\n");
    while (ptr->next != ptr) {
      printf("(%d,%d) ", ptr->key, ptr->data);
      ptr = ptr->next;
    }
  }
  
  if (ptr != NULL) {
      printf("(%d,%d) ", ptr->key, ptr->data);
  }
  
  printf(" ]");
}

void main() {
  insertFirst(1, 10);
  insertFirst(2, 20);
  insertFirst(3, 30);
  insertFirst(4, 1);
  insertFirst(5, 40);
  insertFirst(6, 56);
  
  printf("Original List: ");
  printList();
 
  printf("\n");
  printf("Count: %d\n", getLength());
  
  printf("\n");
  deleteAll();
  printf("\nList after deleting all items: ");
  printList();
}