
#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

#define MEMSIZE 4096 //change number of memsize to change total memory space. 

static char memory[MEMSIZE]; 


void* mymalloc(size_t size,  char* file, int line ){

    metadata* first = (metadata*)(&(memory[0]));
    unsigned int offset =  sizeof(metadata); //size of each node that is stored

    if(size > (MEMSIZE - offset)){
            printf("Malloc failed for %s line %d\n", file, line);
            perror("Not enough memory.\n");
            exit(EXIT_FAILURE);
    }

   if (size<=32){
       size = 32;
   }else if (size<=64){
       size = 64;
   }else if (size<=128){
       size = 128;
   }else if (size<=256){
       size = 256;
   }else if (size<=512){
       size = 512;
   }else if (size<=1024){
       size = 1024;
   }else if (size<=2048){
       size = 2048;
   }else if (size<=3072){
       size = 3072;
   }

    

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
        metadata* candidatenext = NULL;
        unsigned int candoccupied = 0;
        unsigned int candidatediff = MEMSIZE;

        while(iterator->next!=NULL){ 
            
          
            occupied = occupied + offset + iterator->next->blocksize;    //keeps track of total occupied space even if blocks are free. marks location of last free block
            

            if(iterator->next->istaken == 0 && iterator->next->blocksize > size){ // keeps track of best usable location based on size
                
                if(iterator->next->blocksize - size < candidatediff){ 
                    
                    candidatediff = iterator->next->blocksize - size; 
                    candidate = iterator->next; 
                    candidatenext = candidate->next; 
                    candoccupied = occupied;

                }

            }
            iterator = iterator->next;

        }
    
        if( (size + occupied  ) > MEMSIZE){
            printf("Malloc failed for %s line %d\n", file, line);
            perror("Not enough memory");
            exit(EXIT_FAILURE);
        }
    
        if(candidate != NULL){

            candidate->istaken = 1; 
            candidate->blocklocation = &(memory[candoccupied]);

            if(candidate->blocksize - size > offset){


            }


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
    metadata* currentnext = pointer->next; 



    if(currentnext->next != NULL){
        


    }


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


 