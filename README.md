# CS214_PA1

Jason Guo, Net ID: jg1715
Armen do your thing here bub

----------Correctness Test Plan Information----------

Test 1: Linked List  

To test if malloc was capable of running as intended, we created and filled  out a linked list to see if the data is stored properly.  

Each Node structure is 20 (or 12 on 32 bit machine) bytes, 4 bytes from the integer data type, 8 bytes from the char pointer, and 8 bytes from the struct Node pointer.  

The head node is filled out manually, while the next 5 nodes are filled in by a loop. Within the node structure are also strings, whose size are dynamically determined by the iteration of the for loop constructing each node of the list.  

By looking at the results of calling the different information in each node, we can see whether data has been properly stored and whether or not any data is overwritten.  

There is a set of manually written outputs that can be used to compare to the actual results of the test case running.  

There is also a random pointer created after freeing the linked list to check that free properly deallocated.  The new pointer's address should equal the address of the first object allocated (the previous head node of the linked list).  

Test 2: Coalescing  

Initially create 3 pointers: output the address of the first and the third pointers.  

Free the 3 pointers, make 2 new ones, the first of them being the same size as the first and second pointers combined.  This should cause malloc to coalesce first and second chunk of memory to create a new larger one to accomodate the fourth pointer.  

To check that this succeeded, fourth pointer should have the same address as first pointer, and fifth pointer should have the same address as third pointer.  

Further tests splitting by freeing fourth and fifth pointers, then creating three new pointers (6-8).  Sixth and seventh pointers should have sizes that add up to that of the larger chunk's (26 * 4 bytes).  Printing out the sixth and eigth pointers should result in the same addresses as first and third pointers respectively.  
------------------------------------------------  
----------Performance Test Information----------  
Stress Test 4:  
Stress Test 5: Allocate 120 chunks, each of random size from 1-28.  At the end of allocation, print out the total number of bytes allocated (not including bytes for meta data) and free all allocations.  
------------------------------------------------