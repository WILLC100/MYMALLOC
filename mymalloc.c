
#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

#define MEMSIZE 4096 //change number of memsize to change total memory space. 

static char memory[MEMSIZE]; 


void* mymalloc(size_t size,  char* file, int line ){

    metadata* first = (metadata*)(&(memory[0]));
    unsigned int offset =  sizeof(metadata); //size of each node that is stored

    if(size > (MEMSIZE - offset)){ //basic oversize error. 
            printf("Malloc failed for %s line %d\n", file, line);
            perror("Not enough memory.\n");
            exit(EXIT_FAILURE);
    }

    //alighnment protocol. Gets buffer to some value divisible by 4. Clean

    unsigned int remainder = size%4;
    remainder = 4-remainder; 
    size = size+remainder;

    

    if(memory[0] == 0){ //first byte check. if 0: first block is free create allocation immediately, else add to data structure
        
        first->istaken = 1; 
        first->blocksize = size; 
        first->blocklocation = &(memory[offset]); 
        first->next = NULL;
        
        return first->blocklocation; 

    }else{

        //Gets to the next usable location 
        unsigned int occupied = offset + first->blocksize; 

        metadata* iterator = first; 
        metadata* candidate = NULL;
        unsigned int candoccupied = 0;
        unsigned int candidatediff = MEMSIZE;

        while(iterator->next!=NULL){  
            

            if(iterator->next->istaken == 0 && iterator->next->blocksize > size){ // keeps track of best usable location based on size
                
                if(iterator->next->blocksize - size < candidatediff){ 
                    
                    candidatediff = iterator->next->blocksize - size; 
                    candidate = iterator->next;     
                    candoccupied = occupied;

                }

            }
            occupied = occupied + offset + iterator->next->blocksize;    //keeps track of total occupied space even if blocks are free. marks location of last free block

            iterator = iterator->next;

        }
    
        if( (size + occupied  ) > MEMSIZE){ // temp size error should update to be more encompassing. 
            printf("Malloc failed for %s line %d\n", file, line);
            perror("Not enough memory");
            exit(EXIT_FAILURE);
        }
    
        if(candidate != NULL){ //if a free block in chain can be used instead of addending to list; 

            candidate->istaken = 1; 

            if(candidate->blocksize - size > offset){ // if the memory block is large enough to partition into an occupied smaller block + free block
                
                metadata* freenode = (metadata*)&(memory[offset+candoccupied+size]);
                freenode->blocksize = candidate->blocksize-size-offset;
                candidate->blocksize = size; 
                metadata* temp = candidate->next; 
                candidate->next = freenode; 
                freenode->next = temp; 
                freenode->istaken = 0; 
                freenode->blocklocation = &(memory[candoccupied+offset+size+offset]);

                
            }

            return candidate->blocklocation; 

        }

        //arranges data for a new node at end of the chain if no suitable location within chain fouond. 

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

void coalesce(metadata* header){

 /*   metadata* current = header; 
    metadata* prior = header; 

    while(current != NULL){
        




    }
 */
}

void myfree(void* pointer,  char* file, int line){

    //search through all blocks to the correct one 
    metadata* iterator = (metadata*) &(memory[0]);
    metadata* header = iterator;
    char* specific = (char*)pointer; 
    

    while(iterator != NULL){

        if(specific == (iterator->blocklocation)){
            
            if(iterator->istaken == 0){
                
                perror("Block has already been freed, cannot double free\n");
                exit(EXIT_FAILURE);
            }

            iterator->istaken = 0;
            coalesce(header);
           
            return; 
        }

        
        iterator = iterator->next; 

    }
    
    printf("Pointer %p does not point to the start of an allocated chunk", pointer);
    perror("Location address cannot be freed");
    exit(EXIT_FAILURE);

    return;
}


 