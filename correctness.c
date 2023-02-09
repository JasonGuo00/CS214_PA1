#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

void printMem() {
    // Print a 64 x 64 display of the memory
    for(int i = 0; i < 64; i++) {
        for(int x = 0; x < 64; x++) {

        }
    }
}

int main(int argc, char** argv) {

    // Creating a linked list structure using mymalloc

    struct Node {
        int data;
        struct Node* next;
    };
    // Create a head node containing the value 100
    struct Node* head = malloc(sizeof(struct Node));
    head->data = 100;
    struct Node* ptr = head;
    // Add 5 nodes to the linked list
    for(int i = 0; i < 5; i++) {
        struct Node* new = malloc(sizeof(struct Node));
        new->data = i;
        new->next = NULL;
        ptr->next = new;
        ptr = ptr->next;
    }
    ptr = head;
    for(int i = 0; i < 6; i++) {
        printf("Node %d contains the value: %d\n", i, ptr->data);
        struct Node* temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
    


}
