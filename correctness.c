#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

int main(int argc, char** argv) {
    //free them

    // Creating a linked list structure using mymalloc

    struct Node {
        int data;
        char* name;
        struct Node* next;
    };
    // Create a head node containing the value 100
    struct Node* head = malloc(sizeof(struct Node));
    printf("Pointer to the Head Node: %p\n", head);
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
        // Each node also has a dynamically size "string"
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

    char* word = malloc(sizeof(char)*5);
    printf("Pointer to word: %p, should be the same address as the previous head node was.  Proof that free properly deallocated memory\n",word);
    free(word);
    



    // Testing Merging of Memory Chunks
    int* temp1 = malloc(sizeof(int)*10);
    int* temp2 = malloc(sizeof(int)*16);
    int* temp3 = malloc(sizeof(int)*6);
    printf("Temp 1 has address: %p\n", temp1);
    printf("Temp 3 has address: %p\n", temp3);
    // Temp1 and Temp2 have a combined size of 4*10 + 4*16
    free(temp1);
    free(temp2);
    free(temp3);
    int* temp4 = malloc(sizeof(int)*26);
    int* temp5 = malloc(sizeof(int));
    printf("Temp 4 has address: %p\n", temp4); // Should have same address as temp1, chunks of temp1 and temp2 should
                                               // have merged to one.  Extra 5 bytes from 2nd header should be included
    printf("Temp 5 has address: %p\n", temp5); // Should have same address as temp 3 if merge worked properly
    free(temp4);
    free(temp5);
    int* temp6 = malloc(sizeof(int)*4);
    int* temp7 = malloc(sizeof(int)*22);
    int* temp8 = malloc(sizeof(int));
    // larger chunk with 4*26 bytes should split into 2 chunks of size 4*4 and 4*22 
    printf("Temp 6 has address: %p\n", temp6);  // Should be equal to temp1 and temp4
    printf("Temp 7 address is: %ld from Temp 6\n", (char*)temp7 - (char*)temp6);  // Should equal (4*4 + 5 (meta offset) = 21)
    printf("Temp 8 has address: %p\n---------------\n", temp8);  // Should be the same as temp3 and temp5 if merge and split works
    free(temp6);
    free(temp7);
    free(temp8);


    // Test error when allocating more bytes than available
    int* error = malloc(sizeof(char)*10000);
    printf("%p\n",error);
    // Test error when pointer is not obtained from malloc
    int error2 = 12345;
    free(&error2);
    // Test error when trying to free freed / unallocated memory
    struct Node* error3 = malloc(sizeof(struct Node));
    free(error3);
    free(error3);
    printf("---------------\n");
    //Test overlapping chunks by filling up the memory array and freeing 25 times
    int overlapping_detected = 0;
    size_t total_payload_size = MAX_BYTES-(3*5); //5 is the size of each chunk header, going to allocate 3 large chunks
    for (int x = 0; x < 50; x++){
        size_t size_left = total_payload_size;
        float pct[] = {(rand()%30 + 12)/100.0, (rand()%30 + 5)/100.0};
        char* big_chunks[3];
        size_t chunk_sizes[3];
        for (int i = 1; i <= 3; i++){
            char* ith_chunk;
            size_t s;
            if (i < 3){
                s = (size_t) size_left*pct[i-1];
               // printf("%ld at %d 1\n", s,x);
                ith_chunk= malloc(s);
                size_left -= s;
            }
            else{
                s = size_left-1;
                //printf("%ld at %d 2\n", s,x);
                ith_chunk=malloc(s);
            }
            for (size_t j = 0; j < s; j++){
                ith_chunk[j] = i+48;
            }
            big_chunks[i-1] = ith_chunk;
            chunk_sizes[i-1] = s;
        }

        //Check that the last payload byte matches (no overlap)
        for (int i = 0; i < 3; i++){
            char* chunk_ptr = big_chunks[i];
            for (int j = 0; j < chunk_sizes[i]; j++){
                if (chunk_ptr[j] != i+1+48){
                    printf("Overlapping detected in chunk %d: This should be %d, not %c!\n", i+1, i+1, chunk_ptr[j]);
                    overlapping_detected = 1;
                    break;
                }
            }
            free(chunk_ptr);
        }

        if (overlapping_detected){
            break;
        }
    }
    
    if (!overlapping_detected){
        printf("Success: No overlapping between big chunks detected\n");
    }
}
