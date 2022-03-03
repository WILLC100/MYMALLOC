#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "mymalloc.h"

int main(int argc, char* argv[])
{   


  
    unsigned int arraysize = 128;
    int *ptr[arraysize];
    struct timeval startTime;
    struct timeval endTime;
    float totalTimeOne = 0;
    float totalTimeTwo = 0;
    float totalTimeThree = 0;
    float totalTimeFour = 0;
    float totalTimeFive = 0;

    for(int i =0;i<arraysize;i++){
        ptr[i] = NULL;
    }
    
    //Test1 See Documentation
    for(int i = 0; i < 50; i++){
        gettimeofday(&startTime, 0);
        for(int j = 0; j < 120; j++){
           
            ptr[j] = (int *) malloc(1);
            free(ptr[j]);
            ptr[j] = NULL;
        }
        gettimeofday(&endTime, 0);
        totalTimeOne = totalTimeOne + ((endTime.tv_sec-startTime.tv_sec)*1000000 
        + (endTime.tv_usec-startTime.tv_usec));
    }
    
    

     for(int i =0; i<arraysize;i++){ //free the whole array 
        if(ptr[i] != NULL){
         //   printf("%d\n", i);
            free(ptr[i]);
            ptr[i] = NULL;
        }
     }  

    //Test2 See Documentation 
      for(int i = 0; i < 50; i++){
        gettimeofday(&startTime, 0);
        for(int j = 0; j < 120; j++){
            ptr[j] = (int *) malloc(1);
        }
        for(int j = 0; j < 120; j++){
            free(ptr[j]);
            ptr[j] = NULL;
        }
        gettimeofday(&endTime, 0);
        totalTimeTwo = totalTimeTwo + ((endTime.tv_sec-startTime.tv_sec)*1000000
        + (endTime.tv_usec-startTime.tv_usec));
    }

     

      for(int i =0; i<arraysize;i++){ //free the whole array 
        if(ptr[i] != NULL){
           // printf("%d\n", i);
            free(ptr[i]);
            ptr[i] = NULL;
        }
      }
      
     
    //Test3 See Documentation

    for(int i = 0; i < 50; i++){
        gettimeofday(&startTime, 0);
        int current = 0; 
        int freecount= 0;
        
        srand(time(NULL));
        
        while(current < 120){
            int randomNumber = rand() % 2;
            // malloc
            if(randomNumber == 0){
                 
                ptr[current] = (int*) malloc(1);          
                current++;
            }
            // free
            else{   
               for(int i =0; i<arraysize; i++){

                   if(ptr[i] != NULL){
            
                        free(ptr[i]);              
                        ptr[i] = NULL;  
                        freecount++;
                        break;
                   }

               }                                
            }          
        }
        gettimeofday(&endTime, 0);
        totalTimeThree = totalTimeThree + ((endTime.tv_sec-startTime.tv_sec)*1000000
        + (endTime.tv_usec-startTime.tv_usec));
        
        for(int i =0; i<arraysize;i++){ //free the whole array 
        if(ptr[i] != NULL){
            free(ptr[i]);
            ptr[i] = NULL;
        }
        
        
    }
    }


     

    for(int i =0; i<arraysize;i++){ //free the whole array 
        if(ptr[i] != NULL){
            free(ptr[i]);
            ptr[i] = NULL;
        }
     }  
    
    // Test4 See Documentation 
    for(int i = 0; i < 50; i++){
        gettimeofday(&startTime, 0);
        for(int j = 0; j < arraysize; j++){
            ptr[j] = malloc(rand()%8+1);
         
        }
         
        gettimeofday(&endTime, 0);

        totalTimeFour = totalTimeFour + ((endTime.tv_sec-startTime.tv_sec)*1000000
        + (endTime.tv_usec-startTime.tv_usec));

        for(int i =0; i<arraysize;i++){

        if(ptr[i] != NULL){
            free(ptr[i]);
            ptr[i] = NULL;
        }
        
        }
    }
    
   

     for(int i =0; i<arraysize;i++){ //free the whole array 
        if(ptr[i] != NULL){
            free(ptr[i]);
            ptr[i] = NULL;
        }
        
     }  

    // Test5 See Documentation
  
    for(int i = 0; i < 50; i++){
        gettimeofday(&startTime, 0);
        
        
        int current = 1;
        int mallocIndex = 0;
        int freeIndex = 0;
        ptr[mallocIndex] = malloc(50);
        
        while( ptr[mallocIndex] !=NULL){
            current++;
            mallocIndex++;
            ptr[mallocIndex] = malloc(50);
        }
        for(freeIndex = 0; freeIndex < mallocIndex; freeIndex+=2){
            free(ptr[freeIndex]); 
            ptr[mallocIndex] = NULL;
        }
        for(mallocIndex = 0; mallocIndex < current-1; mallocIndex+=2){
            ptr[mallocIndex] = malloc(35);
        }
        for(freeIndex = 0; freeIndex < current-1; freeIndex+=1){
            free(ptr[freeIndex]);
            ptr[freeIndex] = NULL;
        }
        gettimeofday(&endTime, 0);
        totalTimeFive = totalTimeFive + ((endTime.tv_sec-startTime.tv_sec)*1000000
        + (endTime.tv_usec-startTime.tv_usec));
    }

    printf("The average time to execute Test 1 %f microseconds\n", totalTimeOne/50);
    printf("The average time to execute Test 2 %f microseconds\n", totalTimeTwo/50);
    printf("The average time to execute Test 3 %f microseconds\n", totalTimeThree/50);
    printf("The average time to execute Test 4 %f microseconds\n", totalTimeFour/50);
    printf("The average time to execute Test 5 %f microseconds\n\n", totalTimeFive/50);

    
    //Test 6 Prints Error if Malloc tries to allocate more than size of available memory 

    printf("\n Test 6 \n");
    void* test6 = malloc(MEMSIZE);
    if(test6 == NULL){
        printf("\n");
    }

    //Test 7 Prints Error if Malloc tries to allocate no memory

    printf("\n Test 7 \n");
    void* test7 = malloc(0);
    if(test7 == NULL){
        printf("\n");
    }
    
    //Test 8 Prints Error if free void pointer 

    printf("\n Test 8 \n");
    void* test8 = NULL;
    free(test8);

    //Test 9 Prints Error if pointer not in bounds of memory 
      printf("\n Test 9 \n");
    void* test9 = (void*)1;
    free(test9);
    
    //Test 10 Prints Error if pointer is freed twice 

    printf("\n Test 10 \n");
    void* test10 = malloc(1);
    free(test10); 
    free(test10);

    //Test 11 Prints Error if pointer is not the start of a block
    printf("\n Test 11\n");
    int* test11 = malloc(sizeof(int)*2);
    free(test11+1);
    free(test11);

    //Test 12 Prints Error if allocation runs out of space to assign 
        printf("\n Test 12\n");
    int count = 0;
    ptr[count] = malloc(50);
    while(ptr[count] != NULL){

        count++;
        ptr[count] = malloc(50);
    }

    for(int i=0; i<count; i++){
        free(ptr[i]);
    }
    //Test 13 Prints Error if freeing a non-allocated block
    printf("\n Test 13\n");
    int* test13 = malloc(1); 
    metadata* test13a = (metadata*)(test13-4); 
    test13a->istaken =0; 
    test13a->blocksize =0;
    free(test13);

    return 0;
}
