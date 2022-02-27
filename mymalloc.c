
#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

#define MEMSIZE 4096 //change number of memsize to change total memory space. 

static char memory[MEMSIZE]; 


void* mymalloc(size_t size,  char* file, int line ){

    
    unsigned int requestedblocksize = size; //holds the requested block size
  
    
    void* temp = NULL;

    if(!memory[0]){ //first byte check. if 0: first block is free create allocation immediately, else create data structure


        metadata* first = (metadata*)&(memory[0]);

        memory[0] = 1; 
        first->blocksize = requestedblocksize; 
        first->nextblock = NULL;
        first->blocklocation = &(memory[13]); 
        

        

    }else{


    }
    return temp; 
     
    

}

void myfree(void* pointer  char* file, int line){


}


 