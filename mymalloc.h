#include <stddef.h>
#ifndef _MYMALLOC_H_
#define _MYMALLOC_H_ 


typedef struct node { //this node type holds the metadata of each block. size of 24. 

    unsigned char istaken;   // 0 for false, 1 for true 
    unsigned char buffer1; 
    unsigned char buffer2;
    unsigned char buffer3;
    unsigned int blocksize; //size of requested block 
    struct node* next; //points to next metadata node; 
    void* blocklocation;    //address of this node's block 
  

} metadata;

void* mymalloc(size_t size, char* file, int line);

void myfree(void* pointer, char* file, int line); 


#define malloc(s) mymalloc(s, __FILE__, __LINE__)
#define free(p) myfree(p, __FILE__, __LINE__)
 
#endif