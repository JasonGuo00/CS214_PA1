#include <sys/time.h>
#include <stdlib.h>
#include "mymalloc.h"
#include <stdio.h>

struct timeval before, after;

long double t0;
long double t1;

struct node{
	char message;
	struct node* next;
};

void free_ll(struct node* ptr){
	if (ptr->next != NULL){
		free_ll(ptr->next);
	}
	free(ptr);
}

int main(int argc, char* argv[argc+1]){

	int runs = 120;

	size_t s = sizeof(char);

	//Task 1//
		long double timer = 0;
		for(int z = 0; z < 50; z++) {
			gettimeofday(&before, NULL);

			for (int i = 0; i < runs; i++){
				void* ptr = malloc(s);
				free(ptr);
			}
		
			gettimeofday(&after, NULL);
			// printf("Task 1 Time: %lf seconds\n", t1-t0);
			if (before.tv_usec > after.tv_usec){
				timer += (1000000-after.tv_usec+before.tv_usec);
			}
			else{
				timer += (after.tv_usec-before.tv_usec);
			}
		}
		printf("Task 1 Average Time: %Lf microseconds\n", timer/50.0);
		
	//--//

	//Task 2//
		timer = 0;
		for(int z = 0; z < 50; z++) {
			gettimeofday(&before, NULL);

			void* ptr_array[runs];
			
			for (int i = 0; i < runs; i++){
				ptr_array[i] = malloc(s);
			}
			for (int i = 0; i < runs; i++){
				free(ptr_array[i]);
			}

			gettimeofday(&after, NULL);
			if (before.tv_usec > after.tv_usec){
				timer += (1000000-after.tv_usec+before.tv_usec);
			}
			else{
				timer += (after.tv_usec-before.tv_usec);
			}
			// printf("Task 2 Time: %lf seconds\n", t1-t0);
		}
		printf("Task 2 Average Time: %Lf microseconds\n", timer / 50.0);
		
	//--//

	//Task 3//
		timer = 0;
		for(int z = 0; z < 50; z++) {
			gettimeofday(&before, NULL);
			int num_mallocs = 0;
			int open_space = 0;

			void* ptr_array2[runs];

			// This implementation frees the most recently allocated space, so basically like a stack
			while(num_mallocs < 120) {
				if(rand() % 2 == 0 && open_space < 120) {
					ptr_array2[open_space] = malloc(s);
					open_space++;
					num_mallocs++;
				}
				else {
					if(open_space > 0) {
						free(ptr_array2[open_space - 1]);
						open_space--;
					}
					// Otherwise, nothing to free, so do nothing this iteration.
				}
			}

			// Free all allocated objects after malloc runs 120 times
			for(int i = 0; i < open_space; i++) {
				free(ptr_array2[i]);
			}

			gettimeofday(&after, NULL);
			if (before.tv_usec > after.tv_usec){
				timer += (1000000-after.tv_usec+before.tv_usec);
			}
			else{
				timer += (after.tv_usec-before.tv_usec);
			}
			// printf("Task 3 Time: %lf seconds\n", t1-t0);
		}
		printf("Task 3 Average Time: %Lf microseconds\n", timer / 50.0);
	//--//
	
	//Task 4//
		timer = 0;
		for(int z = 0; z < 50; z++) {
			gettimeofday(&before, NULL);

			int num_lines = 0;
			struct node* prev = 0;
			struct node* head = 0;
			for (int i = 0; i < 26; i++){
				num_lines++;
				struct node* new_node = (struct node*) malloc(sizeof(struct node));
				new_node->next = NULL;
				new_node->message = 65+i;
				if (prev != 0){
					prev->next = new_node;
				}
				else{
					head = new_node;
				}
				prev = new_node;
			}
			
			free_ll(head);

			gettimeofday(&after, NULL);
			if (before.tv_usec > after.tv_usec){
				timer += (1000000-after.tv_usec+before.tv_usec);
			}
			else{
				timer += (after.tv_usec-before.tv_usec);
			}
			// printf("Task 4 Time: %lf seconds\n", t1-t0);
		}
		printf("Task 4 Average Time: %Lf microseconds \n", timer / 50.0);
		
	//--//

	//Task 5//
		timer = 0;
		for(int z = 0; z < 50; z++) {
			gettimeofday(&before, NULL);

			void* ptr_array3[runs];

			// run 120 times
			for(int i = 0; i < runs; i++) {
				int rn = (rand() % 28)+1;
				ptr_array3[i] = malloc(rn);
			}
			
			int amt_allocated = 0;
			for(int i = 0; i < runs; i++) {
				byte* chunk = ptr_array3[i];
				chunk -= 5;
				amt_allocated = amt_allocated + *((unsigned int*)chunk);
				free(ptr_array3[i]);
			}

			//printf("Amount Allocated in Run %d of Task 5: %d\n", z, amt_allocated);

			gettimeofday(&after, NULL);
			// printf("Task 5 Time: %lf seconds\n", t1-t0);
			if (before.tv_usec > after.tv_usec){
				timer += (1000000-after.tv_usec+before.tv_usec);
			}
			else{
				timer += (after.tv_usec-before.tv_usec);
			}
		}
		printf("Task 5 Average Time: %Lf microseconds\n", timer / 50.0);
		
	//--//

	return EXIT_SUCCESS;
}