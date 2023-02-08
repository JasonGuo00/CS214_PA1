#include <stdlib.h>
#include "mymalloc.h"
#include <stdio.h>

#define GETSIZE(INDEX) *((unsigned int*)&memory[INDEX])

static byte memory[MAX_BYTES];

// to retrive the "size" of the memory chunk:  *((unsigned int*) &memory[i])

void* mymalloc(size_t size, char* file, int line){
	void* payload_ptr = 0;

	if (size == 0){
		return payload_ptr; //return 0 ptr
	}
		
	//memory[i] is start of chunk header
	//memory[i -> i+1] = size, memory[i+2] = true or false if allocated
	int seq_space_found = 0;
	int i;
	for (i = 0; i+size+5 < MAX_BYTES; i += GETSIZE(i) + 5){
		unsigned int chunk_size = GETSIZE(i);
		char is_allocated = memory[i+4];
		if (is_allocated == 0){
			if (chunk_size == 0){
				//This chunk has never been allocated before,
				//meaning no bytes ahead of it have been allocated either, so we
				//don't need to worry about overwriting
				GETSIZE(i) = size;
				memory[i+4] = 1;
				payload_ptr = &(memory[i+5]);
				//finished allocating, stop searching
				break;
			}
			else{
				int bytes_left = seq_space_found+chunk_size-size; //size of all previous open chunks - size of payload we want to allocate
				if (bytes_left < 0){
					//chunk isn't big enough, keep searching
					seq_space_found += chunk_size+5;
				}
				else {
					//found enough unallocated space, allocate chunk(s)
					int new_header_index = i - seq_space_found;
					GETSIZE(new_header_index) = size;
					memory[new_header_index+4] = 1;
					payload_ptr = &(memory[new_header_index+5]);
					
					//minimum size of a chunk is 6 (four bytes for size, one byte for isAllocated,
					//and one byte for payload)
					if (bytes_left >= 6){
						//there is room for another chunk, so split into two
						int split_header_index = new_header_index+5+size;
						GETSIZE(split_header_index) = bytes_left-5;
						memory[split_header_index+4] = 0;
					}
					else{
						//there are a couple extra bytes in this chunk but not enough to 
						//split the chunk into two. include these spare bytes in the chunk 
						//we just allocated
						GETSIZE(new_header_index) += bytes_left;
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
	for (i = 0; i < MAX_BYTES; i += GETSIZE(i)+5){
		if (&(memory[i+5]) == ptr){
			isPayloadHeader = true;
			break;
		}
		if (GETSIZE(i)+5 == 0){
			//not supposed to happen, but if it somehow does, throw the "pointer
			//does not point to payload header error" to prevent infinite loop
			break;
		}
	}
	if (!isPayloadHeader){
		printf("Error (%s line %d): Pointer %p does not point to payload header\n", file, line, ptr);
		return;
	}
	
	if (memory[i+4] == 0){
		//Was already freed or never allocated
		printf("Error (%s line %d): Attempt to free freed/unallocated memory address\n",  file, line);
		return;
	}
	
	//Errors handled//
	
	//set chunk allocation byte to freed/unallocated
	memory[i+4] = 0;
}

void* myrealloc(void* ptr, size_t s, char* file, int line){
	myfree(ptr, file, line);

	void* new_ptr = mymalloc(s, file, line);
	int old_ptr_index = ((byte*) ptr)-(&memory[0]); //subtract memory addresses to get index in memory
	unsigned payload_size_of_old_ptr = GETSIZE(old_ptr_index); //check how many bytes we have to copy
	if (new_ptr != ptr){
		//only memcpy if we had to move the chunk somewhere else
		memcpy(new_ptr, ptr, payload_size_of_old_ptr);
	}

	return new_ptr;
}