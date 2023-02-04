#include <stdlib.h>
#include "mymalloc.h"
#include <stdio.h>

static byte memory[MAX_BYTES];

void* mymalloc(size_t size, char* file, int line){
	if (size == 0){
		return (void*) 0;
	}

	void* payload_ptr = 0;
		
	//memory[i] is start of chunk header
	//memory[i] = size, memory[i+1] = true or false if allocated
	int seq_space_found = 0;
	int i;
	for (i = 0; i+size+2 < MAX_BYTES; i += memory[i]+2){
		int chunk_size = memory[i];
		char is_allocated = memory[i+1];
		if (is_allocated == 0){
			if (chunk_size == 0){
				//This chunk has never been allocated before,
				//meaning no bytes ahead of it have been allocated either, so we
				//don't need to worry about overwriting
				memory[i] = size;
				memory[i+1] = 1;
				payload_ptr = &(memory[i+2]);
				//finished allocating, stop searching
				break;
			}
			else{
				int bytes_left = seq_space_found+chunk_size-size; //size of all previous open chunks - size of payload we want to allocate
				if (bytes_left < 0){
					//chunk isn't big enough, keep searching
					seq_space_found += chunk_size+2;
				}
				else {
					//found enough unallocated space, allocate chunk(s)
					int new_header_index = i - seq_space_found;
					memory[new_header_index] = size;
					memory[new_header_index+1] = 1;
					payload_ptr = &(memory[new_header_index+2]);
					
					//minimum size of a chunk is 3 (one byte for size, one byte for isAllocated,
					//and one byte for payload)
					if (bytes_left >= 3){
						//there is room for another chunk, so split into two
						int split_header_index = new_header_index+2+size;
						memory[split_header_index] = bytes_left;
						memory[split_header_index+1] = 0;
					}
					else{
						//there are a couple extra bytes in this chunk but not enough to 
						//split the chunk into two. include these spare bytes in the chunk 
						//we just allocated
						memory[new_header_index] += bytes_left;
					}
					
					//finished allocating, stop searching
					break;
				}
			}
		}
		else{
			//Ran into an already allocated chunk. There isn't enough free
			//sequential space between this chunk header and the last unallocated chunk header
			//to make an adequate allocation
			seq_space_found = 0;
		}

	}

	if (payload_ptr == 0){
		printf("Error (%s line %d): Unable to allocate. Not enough space\n",  file, line);
	}

	return payload_ptr;
}

void myfree(void* ptr, char* file, int line){
	//Handle errors//
	
	if (ptr < (void*) &(memory[0]) || ptr > (void*) &(memory[MAX_BYTES-1])){
		//ptr address is outside of the array
		printf("Error (%s line %d): Pointer %p not obtained with malloc\n", file, line, ptr);
		return;
	}

	bool isPayloadHeader = false;
	
	int i;
	for (i = 0; i < MAX_BYTES; i += memory[i]+2){
		if (&(memory[i+2]) == ptr){
			isPayloadHeader = true;
			break;
		}
		if (memory[i]+2 == 0){
			//not supposed to happen, but if it somehow does, throw the "pointer
			//does not point to payload header error" to prevent infinite loop
			break;
		}
	}
	if (!isPayloadHeader){
		printf("Error (%s line %d): Pointer %p does not point to payload header\n", file, line, ptr);
		return;
	}
	
	if (memory[i+1] == 0){
		//Was already freed or never allocated
		printf("Error (%s line %d): Attempt to free freed/unallocated memory address\n",  file, line);
		return;
	}
	
	//Errors handled//
	
	//set chunk allocation byte to freed/unallocated
	memory[i+1] = 0;
}