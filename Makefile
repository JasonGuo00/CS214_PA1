all: go

clean:
	rm -rf mymalloc.o
	rm -rf memgrind
	rm -rf err
	rm -rf correctness

go: memgrind.c 
	make clean
	gcc -Wall -Werror -o mymalloc.o -c mymalloc.c
	gcc -Wall -Werror memgrind.c mymalloc.o -o memgrind 
	gcc -Wall -Werror err.c mymalloc.o -o err
	gcc -Wall -Werror correctness.c mymalloc.o -o correctness