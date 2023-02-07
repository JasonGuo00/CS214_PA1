#ifndef MYMALLOC_H
#define MYMALLOC_H

	#define MAX_BYTES 4096
	
	enum bool{false,true};
	
	typedef enum bool bool;
	typedef char byte;
	
	void* mymalloc(size_t s, char* file, int line);
	void myfree(void* ptr, char* file, int line);
	void* myrealloc(void* ptr, size_t s, char* file, int line);

	#define malloc(s) mymalloc(s, __FILE__, __LINE__)
	#define free(ptr) myfree(ptr, __FILE__, __LINE__)
	#define realloc(ptr, s) myrealloc(ptr, s, __FILE__, __LINE__)
	
#endif