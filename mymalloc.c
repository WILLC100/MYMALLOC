
#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

#define MEMSIZE 4096 //change number of memsize to change total memory space. 

static char memory[MEMSIZE]; 


void* mymalloc(size_t size,  char* file, int line ){

    metadata* first = (metadata*)(&(memory[0]));
    unsigned int offset =  sizeof(metadata); //size of each node that is stored

    if(memory[0] == 0){ //first byte check. if 0: first block is free create allocation immediately, else add to data structure

        if(size > MEMSIZE){
            printf("Malloc failed for %s line %d\n", file, line);
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
            printf("Malloc failed for %s line %d\n", file, line);
            perror("Not enough memory");
            exit(EXIT_FAILURE);
        }

        //arranges data for it 

        metadata* newnode = (metadata*)&(memory[occupied]);
        iterator->next = newnode; 
        newnode->istaken = 1; 
        newnode->blocksize = size; 
        newnode->blocklocation = &(memory[occupied+offset]);
        newnode->next = NULL;

        return newnode->blocklocation;

    }
    return NULL;

}

void coalesce(metadata* pointer){

    metadata* current = pointer; 
    metadata* 


}

void myfree(void* pointer,  char* file, int line){

    //search through all blocks to the correct one 
    metadata* iterator = (metadata*) &(memory[0]);
    metadata* behinditerator = iterator; 
    char* specific = (char*)pointer; 

    while(iterator != NULL){

        if(&*specific == &*(iterator->blocklocation)){
            
            if(iterator->istaken == 0){
                
                perror("Block has already been freed, cannot double free\n");
                exit(EXIT_FAILURE);
            }

            iterator->istaken = 0;
            coalesce(behinditerator);

            return;
        }

        behinditerator = iterator;
        iterator = iterator->next; 

    }


    
    printf("Pointer %p does not point to the start of an allocated chunk", pointer);
    perror("Location address cannot be freed");
    exit(EXIT_FAILURE);

    return;
}


 