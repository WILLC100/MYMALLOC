
#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

#define MEMSIZE 4096 //change number of memsize to change total memory space. 

static char memory[MEMSIZE]; 


void* mymalloc(size_t size,  char* file, int line ){

    
    metadata* first = (metadata*)(&(memory[0]));
    unsigned int offset =  sizeof(metadata); //size of each node that is stored

    void* temp = NULL;

    if(memory[0] == 0){ //first byte check. if 0: first block is free create allocation immediately, else create data structure

        if(size > MEMSIZE){
            perror("Not enough memory.\n");
            exit(EXIT_FAILURE);
        }

        first->istaken = 1; 
        first->blocksize = size; 
        first->blocklocation = &(memory[offset]); 
        first->next = NULL;
        
        return first->blocklocation; 

    }else{

        //Gets to the next usable location 
        unsigned int occupied = offset + first->blocksize; 

        metadata* iterator = first; 
        while(iterator->next!=NULL){ 
            
            occupied = occupied + offset + iterator->next->blocksize;    //keeps track of total occupied space
            iterator = iterator->next;
        }

        if(size + occupied > MEMSIZE){
            perror("Not enough memory");
            exit(EXIT_FAILURE);
        }

        //arranges data for it 
        iterator->next = (metadata*)&(memory[occupied]);
        





    }
    return temp;
     
    

}

void myfree(void* pointer,  char* file, int line){

    return;
}


 