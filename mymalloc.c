
#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"


static char memory[MEMSIZE];  

void* mymalloc(size_t size,  char* file, int line ){

    metadata* first = (metadata*)(&(memory[0]));  
    unsigned int offset =  sizeof(metadata); //size of each node that is stored
   
    //Undersize error 

    if(size == 0){
        printf("Malloc failed for file %s line %d\n", file, line);
        perror("Cannot allocate 0 memory\n");
       // exit(EXIT_FAILURE);
       return NULL;
    }

    //alighnment protocol. Gets buffer to some value divisible by 4.  
  
    unsigned int remainder = size%4;
    remainder = 4-remainder; 
    size = size+remainder;

    //Initial oversize error

    if(size > (MEMSIZE - offset)){ 
            printf("Malloc failed for %s line %d\n", file, line);
            perror("Not enough memory.\n");
            //exit(EXIT_FAILURE);
           return NULL;
    }
    //Allocations 

    if(first->istaken ==0 && first->blocksize == 0){ //first node check. if 0: first block is free and unallocated create allocation immediately, else add to data structure

        first->istaken = 1; 
        first->blocksize = size; 
        first->next = NULL;
     
        return &(memory[offset]); 

    }else{ // first node is allocated and is/isnot taken 

        //Gets to the next usable location 
        unsigned int occupied = 0; 
        metadata* iterator = first; 
        metadata* end = NULL;
        metadata* candidate = NULL;
        unsigned int candoccupied = 0;
        unsigned int candidatediff = MEMSIZE;

        while(iterator !=NULL){  
            
            if(iterator->istaken == 0 && iterator->blocksize >= size){ // keeps track of best usable location based on size
                
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
                freenode->blocksize = (((candidate->blocksize)-size)-offset);        
              
                candidate->blocksize = size; 
                metadata* temp = candidate->next; 
                candidate->next = freenode; 
                
                freenode->next = temp; 
                freenode->istaken = 0;            
            } 
     
            return &(memory[candoccupied+offset]); 

        }
        //arranges data for a new node at end of the chain if no suitable location within chain fouond. 

        if( (size + occupied + offset ) > MEMSIZE){ // Full memory case
            printf("Malloc failed for %s line %d\n", file, line);
            printf("Not enough free memory for allocation. %ld Total bytes needed. %d Total bytes available.\n", size+offset, MEMSIZE-occupied);    
            perror("Malloc runtime error");
           // exit(EXIT_FAILURE);
            return NULL;
        }

        metadata* newnode = (metadata*)&(memory[occupied]);
        end->next = newnode; 
        newnode->istaken = 1; 
        newnode->blocksize = size; 
        newnode->next = NULL;
 
        return &(memory[occupied+offset]);

    }
    return NULL;

}

void coalesce(metadata* first){

    metadata* current = first;
    metadata* cnext = first->next; 
    int coal = 0;

    if(cnext == NULL){
        return;
    }

    if(current->istaken == 0 && cnext->istaken ==0){ //in the case that the prior and current node are free, coalesce. 

        current->next = cnext->next; 
        current->blocksize = sizeof(metadata) + current->blocksize + cnext->blocksize; 
        //printf("COALESCE NEW SIZE %d\n", current->blocksize);
        coal = 1;

    } 

    metadata* c2 = cnext->next; 

    if(c2 == NULL){ //no after node after current node, can return empty

        return;
    }

    if(coal == 1 && c2->istaken ==0){ // if first 2 coalesced, coalesce the first and third node. 

        current->next = c2->next; 
        current->blocksize = sizeof(metadata) + current->blocksize + c2->blocksize; 
      //  printf("COALESCE NEW SIZE %d\n", current->blocksize);
        return;

    }else if (coal == 0 && cnext->istaken==0 && c2->istaken == 0){ // if first 2 did not coalesce, check if second and third are free, coalesce

        cnext->next = c2->next;
        cnext->blocksize = sizeof(metadata ) + cnext->blocksize + c2->blocksize;
      //  printf("COALESCE NEW SIZE %d\n", cnext->blocksize);
        return; 
    }else{ //no coalesce scenario

        return; 
    }
    
 
}

void myfree(void* pointer,  char* file, int line){

    char* lead = (char*)pointer; 
    if(pointer == NULL){
        printf("Failed free for file %s line %d\n", file, line);
        perror("Cannot Free, Null Pointer Exception\n");
       // exit(EXIT_FAILURE);
       return;
    }

    
    
    if(&(*lead) < &memory[0] || &(*lead) > &memory[MEMSIZE-1]){ // Out of bounds error 
        printf("Failed free for file %s line %d\n", file, line);
        perror("Pointer out of bounds of memory\n");
      //  exit(EXIT_FAILURE);
      return;
    }
    
    //search through all blocks to the correct one 

    metadata* iterator = (metadata*) &(memory[0]);
    metadata* prior = iterator;
    metadata* current = pointer-(sizeof(metadata));

    

    while(iterator!=NULL){

        if(iterator == current){
            
            if(current->istaken == 0 && current->blocksize > 0){ // free block
                printf("Block is not allocated, cannot free at address %p\n Failed free for file %s line %d\n", current, file, line);
                perror("Double free\n");
               // exit(EXIT_FAILURE);
               return;
            }else if(current->istaken == 0 && current->blocksize == 0){ //not allocated block
                 printf("Block is not allocated, cannot free at address %p\n Failed free for file %s line %d\n", current, file, line);
                perror("Cannot free unallocated block\n");
               // exit(EXIT_FAILURE);
               return;
            }
            current->istaken =0; 
                if(current->next == NULL){ //if the block is the last in the chain.
                    current->blocksize =0;
                    prior->next=NULL;

                    return;
                }
            coalesce( prior);

            return;
        }
        prior = iterator;
        iterator = iterator->next;
    }
 
    printf("Pointer %p does not point to the start of an allocated chunk\n Failed free for file %s line %d\n", pointer, file, line);
    perror("Location address cannot be freed\n");
    //exit(EXIT_FAILURE);

    return;
}



 