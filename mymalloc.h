
#ifndef _MYMALLOC_H_
#define _MYMALLOC_H_ 




void* mymalloc(size_t size, char* file, int line);

void free(void* pointer, char* file, int line); 

#endif