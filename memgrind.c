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

		void* ptr_array2[runs];
		for (int i = 0; i < runs; i++){
			if (rand()%2==0){
				ptr_array2[i] = malloc(s);
			}
			else{
				
			}
		}

		set_stopwatch();
		printf("Task 4 Time: %lf seconds\n", t1-t0);
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

	return EXIT_SUCCESS;
}