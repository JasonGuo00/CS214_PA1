#include <sys/time.h>
#include <stdlib.h>
#include "mymalloc.h"
#include <stdio.h>

struct timeval before, after;

long double t0;
long double t1;

int main(int argc, char* argv[argc+1]){

	int runs = 120;

	time_t t;
	srand((unsigned) time(&t));

	size_t s = sizeof(char);

	//Task 1//
		long double time = 0;
		for(int z = 0; z < 50; z++) {
			gettimeofday(&before, NULL);

			for (int i = 0; i < runs; i++){
				void* ptr = malloc(s);
				free(ptr);
			}
		
			gettimeofday(&after, NULL);
			// printf("Task 1 Time: %lf seconds\n", t1-t0);
			time += (after.tv_usec-before.tv_usec);
		}
		printf("Task 1 Average Time: %Lf microseconds\n", time/50.0);
		
	//--//

	//Task 2//
		time = 0;
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
			time += (after.tv_usec-before.tv_usec);
			// printf("Task 2 Time: %lf seconds\n", t1-t0);
		}
		printf("Task 2 Average Time: %Lf microseconds\n", time / 50.0);
		
	//--//

	//Task 3//
		time = 0;
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
			time += (after.tv_usec-before.tv_usec);
			// printf("Task 3 Time: %lf seconds\n", t1-t0);
		}
		printf("Task 3 Average Time: %Lf microseconds\n", time / 50.0);
		
	//--//

	//Task 4//
		time = 0;
		for(int z = 0; z < 50; z++) {
			gettimeofday(&before, NULL);

			char* str = malloc(5);
			str[0] = 't';
			str[1] = 'e';
			str[2] = 's';
			str[3] = 't';
			str[4] = 0;

			// printf("%d\n", rand());

			printf("%s\n", str);
			free(str);

			gettimeofday(&after, NULL);
			time += (after.tv_usec-before.tv_usec);
			// printf("Task 4 Time: %lf seconds\n", t1-t0);
		}
		printf("Task 4 Average Time: %Lf microseconds \n", time / 50.0);
		
	//--//

	//Task 5//
		time = 0;
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

			printf("Amount Allocated in Run %d of Task 5: %d\n", z, amt_allocated);

			gettimeofday(&after, NULL);
			// printf("Task 5 Time: %lf seconds\n", t1-t0);
			time += (after.tv_usec-before.tv_usec);
		}
		printf("Task 5 Average Time: %Lf microseconds\n", time / 50.0);
		
	//--//

	return EXIT_SUCCESS;
}