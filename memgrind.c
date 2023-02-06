#include <sys/time.h>
#include <stdlib.h>
#include "mymalloc.h"
#include <stdio.h>

struct timeval stopwatch;

double t0;
double t1;

void set_stopwatch(){
	double* ptr;
	gettimeofday(&stopwatch, NULL);
	if (t1 >= t0){
		ptr = &t0;
	}
	else{
		ptr = &t1;
	}
	*ptr = stopwatch.tv_sec + (stopwatch.tv_usec/1000000.0);
}

int main(int argc, char* argv[argc+1]){

	int runs = 120;

	time_t t;
	srand((unsigned) time(&t));

	//Task 1//
		set_stopwatch();

		size_t s = sizeof(char);
		for (int i = 0; i < runs; i++){
			void* ptr = malloc(s);
			free(ptr);
		}
	
		set_stopwatch();
		printf("Task 1 Time: %lf seconds\n", t1-t0);
	//--//

	//Task 2//
		set_stopwatch();

		void* ptr_array[runs];
		
		for (int i = 0; i < runs; i++){
			ptr_array[i] = malloc(s);
		}
		for (int i = 0; i < runs; i++){
			free(ptr_array[i]);
		}

		set_stopwatch();
		printf("Task 2 Time: %lf seconds\n", t1-t0);
	//--//

	//Task 3//
		set_stopwatch();
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

		set_stopwatch();
		printf("Task 3 Time: %lf seconds\n", t1-t0);
	//--//

	//Task 4//
		set_stopwatch();

		char* str = malloc(5);
		str[0] = 't';
		str[1] = 'e';
		str[2] = 's';
		str[3] = 't';
		str[4] = 0;

		printf("%d\n", rand());

		printf("%s\n", str);
		free(str);

		set_stopwatch();
		printf("Task 4 Time: %lf seconds\n", t1-t0);
	//--//

	//Task 5//
		set_stopwatch();

		void* ptr_array3[runs];

		int index = 0;
		// run 120 times, allocating random numbers of bytes and freeing if there's no room left.
		for(int i = 0; i < runs; i++) {
			ptr_array3[index] = malloc((rand() % (((MAX_BYTES-5)/120)) - 1) + 1);
			index++;
		}

		for(int i = 0; i < 10; i++) {
			byte* chunk = ptr_array3[rand() % runs];
			chunk -= 5;
			printf("Random Chunk %d has size: %d\n", i, *((unsigned int*)chunk));
		}

		for(int i = 0; i < index; i++) {
			if(ptr_array3[i])
			free(ptr_array3[i]);
		}

		set_stopwatch();
		printf("Task 5 Time: %lf seconds\n", t1-t0);
	//--//

	return EXIT_SUCCESS;
}