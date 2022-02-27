
#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

#define MEMSIZE 4096 //change number of memsize to change total memory space. 

static char memory[MEMSIZE]; 

typedef struct node {

    unsigned char isfree;    // 0 for false, 1 for true 
    unsigned int blocksize; //size of requested block 
    struct node* nextblock; // points to next metadata node; 
    void* blocklocation;    //address of this node's block 

} metadata;

void* malloc(size_t size ){

    
    unsigned int requestedblocksize = size; //holds the requested block size
  
    
 

    if(!memory[0]){ //first byte check. if 0: first block is free create allocation immediately, else create data structure


        metadata* first = &(memory[0]);

        memory[0] = 1; 
        first->blocksize = requestedblocksize; 
        first->nextblock = NULL;
        first->blocklocation = &(memory[13]); 
        

        

    }else{


    }
     
    

}

void free(void* pointer ){


}


 