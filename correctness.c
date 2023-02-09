#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

int main(int argc, char** argv) {

    // Creating a linked list structure using mymalloc

    struct Node {
        int data;
        char* name;
        struct Node* next;
    };
    // Create a head node containing the value 100
    struct Node* head = malloc(sizeof(struct Node));
    head->data = 100;
    char* n = malloc(sizeof(char)*5);
    n[0] = 'H'; n[1] = 'E'; n[2] = 'A'; n[3] = 'D'; n[4] = '\0';
    head->name = n;
    struct Node* ptr = head;
    // Add 5 nodes to the linked list
    for(int i = 0; i < 5; i++) {
        struct Node* new = malloc(sizeof(struct Node));
        new->data = i;
        new->next = NULL;
        char* name = malloc(sizeof(char)*(i+2));
        name[i+1] = '\0';
        for(int x = 0; x < i+1; x++) {
            name[x] = 'a';
        }
        new->name = name;
        printf("%s\n", ptr->name);
        ptr->next = new;
        ptr = ptr->next;
    }
    ptr = head;
    printf("---------------\n");
    printf("Test Results:\n");
    for(int i = 0; i < 6; i++) {
        printf("Node %d contains the value: %d and the name: %s\n", i, ptr->data, ptr->name);
        struct Node* temp = ptr;
        ptr = ptr->next;
        free(temp->name);
        free(temp);
    }
    printf("---------------\n");
    printf("Expected Results:\n");
    printf("Node 0 contains the value: 100 and the name: HEAD\n");
    printf("Node 1 contains the value: 0 and the name: a\n");
    printf("Node 2 contains the value: 1 and the name: aa\n");
    printf("Node 3 contains the value: 2 and the name: aaa\n");
    printf("Node 4 contains the value: 3 and the name: aaaa\n");
    printf("Node 5 contains the value: 4 and the name: aaaaa\n");
    printf("---------------\n");

    


}
