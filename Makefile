all: go

clean:
	rm -rf mymalloc.o
	rm -rf memgrind

go: memgrind.c 
	make clean
	gcc -Wall -Werror -o mymalloc.o -c mymalloc.c
	gcc -Wall -Werror memgrind.c mymalloc.o -o memgrind 