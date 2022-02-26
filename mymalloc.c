
#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

#define MEMSIZE 4096 //change number of memsize to change total memory space. 

static char memory[MEMSIZE]; 

typedef struct node {

    unsigned int isfree;    // 0 for false, 1 for true 
    unsigned int blocksize; //size of requested block 
    struct node* nextblock; // points to next metadata node; 
    void* blocklocation;    //address of this node's block 

} metadata;




