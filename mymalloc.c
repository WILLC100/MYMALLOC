
#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

#define MEMSIZE 4096 //change number of memsize to change total memory space. 

static char memory[MEMSIZE];  


void* mymalloc(size_t size,  char* file, int line ){

    metadata* first = (metadata*)(&(memory[0])); 
    unsigned int offset =  sizeof(metadata); //size of each node that is stored
   
    //Undersize error 

    if(size == 0){
        printf("Malloc failed for file %s line %d\n", file, line);
        perror("Cannot allocate 0 memory\n");
        exit(EXIT_FAILURE);
    }

    //alighnment protocol. Gets buffer to some value divisible by 4. Clean
  
    unsigned int remainder = size%4;
    remainder = 4-remainder; 
    size = size+remainder;

    //Initial oversize error

    if(size > (MEMSIZE - offset)){ 
            printf("Malloc failed for %s line %d\n", file, line);
            perror("Not enough memory.\n");
            exit(EXIT_FAILURE);
    }
    
    //Allocations 

    if(first->istaken ==0 && first->blocksize == 0){ //first node check. if 0: first block is free and unallocated create allocation immediately, else add to data structure
        
        first->istaken = 1; 
        first->blocksize = size; 
        first->blocklocation = &(memory[offset]); 
     
        return first->blocklocation; 

    }else{

        //Gets to the next usable location 
        unsigned int occupied = 0; 

        metadata* iterator = first; 
        metadata* end = NULL;
        metadata* candidate = NULL;
        unsigned int candoccupied = 0;
        unsigned int candidatediff = MEMSIZE;

        while(iterator !=NULL){  
            

            if(iterator ->istaken == 0 && iterator->blocksize > size){ // keeps track of best usable location based on size
                
                if(iterator->blocksize - size < candidatediff){ //minimum
                    
                    candidatediff = iterator->blocksize - size; 
                    candidate = iterator;     
                    candoccupied = occupied;
                }
            }

            occupied = occupied + offset + iterator->blocksize;    //keeps track of total occupied space even if blocks are free. marks location of last free block
            
            if(iterator->next == NULL){
                end = iterator; 
            }
            iterator = iterator->next;
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

        if( (size + occupied + offset ) > MEMSIZE){ // temp size error should update to be more encompassing. 
            printf("Malloc failed for %s line %d\n", file, line);
            perror("Not enough memory, free allocated memory\n");
            exit(EXIT_FAILURE);
        }

        metadata* newnode = (metadata*)&(memory[occupied]);
        end->next = newnode; 
        newnode->istaken = 1; 
        newnode->blocksize = size; 
        newnode->blocklocation = &(memory[occupied+offset]);
        newnode->next = NULL;

          

        return newnode->blocklocation;

    }
    return NULL;

}

void coalesce(metadata* first){

    metadata* current = first;
    metadata* cnext = first->next; 

    while(cnext != NULL){
       
        
        if(current->istaken == 0 && cnext->istaken == 0){

            current->next = cnext->next; 
            current->blocksize = sizeof(metadata) + current->blocksize + cnext->blocksize; 

        }
        current = current->next;
        cnext = cnext->next; 
    }
    return; 
 
}

void myfree(void* pointer,  char* file, int line){

    char* lead = (char*)pointer; 
    
    if(&(*lead) < &memory[0]){ // underbounds error 
        perror("Pointer underbounds of memory\n");
        exit(EXIT_FAILURE);
    }
    if(&(*lead) > &memory[MEMSIZE-1]){ // overbounds error 
        perror("Pointer overbounds of memory\n");
        exit(EXIT_FAILURE);
    }
    

    //search through all blocks to the correct one 
    metadata* iterator = (metadata*) &(memory[0]);
    metadata* prior = iterator;
    char* specific = (char*)pointer; 
     

    while(iterator != NULL){

        if(specific == (iterator->blocklocation)){
            

            if(iterator->istaken == 0){
                
                perror("Block has already been freed, cannot double free\n");
                exit(EXIT_FAILURE);
            }


            iterator->istaken = 0;
            coalesce(prior);
           
            return; 
        }

        prior = iterator; 
        iterator = iterator->next; 

    }
    
    printf("Pointer %p does not point to the start of an allocated chunk\n", pointer);
    perror("Location address cannot be freed\n");
    exit(EXIT_FAILURE);

    return;
}


 