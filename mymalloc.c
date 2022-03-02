
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

        printf("First success\n");
        first->istaken = 1; 
        first->blocksize = size; 
        first->next = NULL;
     
        return &(memory[offset]); 

    }else{ // first is allocated and is/isnot taken 

        //Gets to the next usable location 
        unsigned int occupied = 0; 

        metadata* iterator = first; 
        metadata* end = NULL;
        metadata* candidate = NULL;
     //   metadata* iprior = iterator;
      //  metadata* candprior = NULL;
        unsigned int candoccupied = 0;
        unsigned int candidatediff = MEMSIZE;

        while(iterator !=NULL){  
            
            printf("Distance %d ", occupied);
            if(iterator->istaken == 0 && iterator->blocksize >= size){ // keeps track of best usable location based on size
                
                if(iterator->blocksize - size < candidatediff){ //minimum
                    
                    candidatediff = iterator->blocksize - size; 
                    candidate = iterator;     
                   // candprior = iprior;
                    candoccupied = occupied;

                }
            }

            occupied = occupied + offset + iterator->blocksize;    //keeps track of total occupied space even if blocks are free. marks location of last free block
            
            if(iterator->next == NULL){
                end = iterator; 
            }
            printf("Address iterator %p\n", iterator);
          //  iprior = iterator; 
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
            if((metadata*)&memory[0] == candidate){
                printf("Candidate is first\n");
            }
            printf("Candidate Success %d\n", candoccupied);
 
            return &(memory[candoccupied+offset]); 

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
        newnode->next = NULL;

        printf("newnode success %d\n", occupied);
      

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
        printf("COALESCE NEW SIZE %d\n", current->blocksize);

        coal = 1;

    } 




    metadata* c2 = cnext->next; 

    if(c2 == NULL){ //no after node after current node, can return empty

        return;
    }

    if(coal == 1 && c2->istaken ==0){ // if first 2 coalesced, coalesce the first and third node. 

        current->next = c2->next; 
        current->blocksize = sizeof(metadata) + current->blocksize + c2->blocksize; 
        printf("COALESCE NEW SIZE %d\n", current->blocksize);

        return;

    }else if (coal == 0 && cnext->istaken==0 && c2->istaken == 0){ // if first 2 did not coalesce, check if second and third are free, coalesce

        cnext->next = c2->next;
        cnext->blocksize = sizeof(metadata ) + cnext->blocksize + c2->blocksize;
        printf("COALESCE NEW SIZE %d\n", cnext->blocksize);

        return; 
    }else{ //no coalesce scenario

        return; 
    }

    

  /*  while(cnext != NULL){
           
        if(current->istaken == 0 && cnext->istaken == 0){

            current->next = cnext->next; 
            current->blocksize = sizeof(metadata) + current->blocksize + cnext->blocksize; 
            printf("COALESCE NEW SIZE %d\n", current->blocksize);
 

        }
        
        cnext = cnext->next; 
        
    } */
    
 
}

void myfree(void* pointer,  char* file, int line){

    if(pointer ==NULL){

        perror("Null Pointer Exception");
        exit(EXIT_FAILURE);
    }

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

    metadata* current = pointer-(sizeof(metadata));

    if(current == iterator ){ //for the first node
        iterator->istaken =0; 

        printf("Free first\n");
        return;
    }

    while(iterator!=NULL){

        printf(" 1 ");

        if(iterator == current){
            
            if(current->istaken == 0 && current->blocksize > 0){ // free block

                perror("Block already freed, cannot double free");
                exit(EXIT_FAILURE);
            }else if(current->istaken == 0 && current->blocksize == 0){ //not allocated block
                perror("Block is not allocated, cannot free");
                exit(EXIT_FAILURE);

            }

            current->istaken =0; 
            if(current->next == NULL){ //if the block is the last in the chain.
                current->blocksize =0;
              prior->next=NULL;

              printf("Free end\n");
              return;
            }
            coalesce( prior);

            printf("Free not first\n");
            return;
        }
        prior = iterator;
        iterator = iterator->next;
    }
 
/*

    if(current->istaken == 1){
        current->istaken = 0; 
        coalesce(iterator);
        return; 
    }else{
        if( current->blocksize > 0 ){
           // printf("%p ", &memory[0]);
          //  printf("%p ", &memory[MEMSIZE-1]);
           // printf("Pointer %p blocklocation %p", pointer, &*current);
            perror("\nCannot free already freed block\n");
            exit(EXIT_FAILURE);

        }else{

            perror("Cannot free non-allocated block\n");
            exit(EXIT_FAILURE);
        }

    }
    
    
    metadata* prior = iterator;
  
     

    while(iterator != NULL){

        if(&*specific == &*(iterator->blocklocation)){
            

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
    */
    printf("Pointer %p does not point to the start of an allocated chunk\n", pointer);
    perror("Location address cannot be freed\n");
    exit(EXIT_FAILURE);

    return;
}


 