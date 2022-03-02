#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "mymalloc.h"

int main(int argc, char* argv[])
{   


  
    unsigned int arraysize = 256;
    int *ptr[arraysize];
    struct timeval startTime;
    struct timeval endTime;
  //  float totalTimeOne = 0;
  //  float totalTimeTwo = 0;
    float totalTimeThree = 0;
   // float totalTimeFour = 0;
   // float totalTimeFive = 0;

    for(int i =0;i<arraysize;i++){
        ptr[i] = NULL;
    }
    
 /*   //Test1
    for(int i = 0; i < 50; i++){
        gettimeofday(&startTime, 0);
        for(int j = 0; j < 120; j++){
            ptr[j] = (int *) malloc(1);

           // printf("Malloc %d", i );

            free(ptr[j]);

           // printf("Free %d ", i);
            ptr[j] = NULL;
        }
        gettimeofday(&endTime, 0);
        totalTimeOne = totalTimeOne + ((endTime.tv_sec-startTime.tv_sec)*1000000 
        + (endTime.tv_usec-startTime.tv_usec));
    }
    
    printf("The average time to execute Test 1 %f milliseconds\n", totalTimeOne/50);

     for(int i =0; i<arraysize;i++){ //free the whole array 
        if(ptr[i] != NULL){
         //   printf("%d\n", i);
            free(ptr[i]);
            ptr[i] = NULL;
        }
     }  
    //Test2
      for(int i = 0; i < 50; i++){
        gettimeofday(&startTime, 0);
        for(int j = 0; j < 120; j++){
            ptr[j] = (int *) malloc(1);
           // printf("Malloc %d\n", j);
        }
        for(int j = 0; j < 120; j++){
            free(ptr[j]);
            //printf("Free %d\n", j);
            ptr[j] = NULL;
        }
        //printf("%d", i);
        gettimeofday(&endTime, 0);
        totalTimeTwo = totalTimeTwo + ((endTime.tv_sec-startTime.tv_sec)*1000000
        + (endTime.tv_usec-startTime.tv_usec));
    }

     printf("The average time to execute Test 2 %f milliseconds\n", totalTimeTwo/50);

      for(int i =0; i<arraysize;i++){ //free the whole array 
        if(ptr[i] != NULL){
           // printf("%d\n", i);
            free(ptr[i]);
            ptr[i] = NULL;
        }
      }
      
     */
    //Test3

        

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

               printf("Malloc %d\n", current);
               printf("Malloc pointer %p\n\n", ptr[current]);
               
                current++;
            }
            // free
            else{
               
                
               for(int i =0; i<arraysize; i++){

                   if(ptr[i] != NULL){
                        printf("    Free %d\n", freecount);
                      // printf("Free %d \n",i);
                        
                        free(ptr[i]);
                        printf("    Pointer %p\n\n", ptr[i]);
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
         //   printf("%d\n", i);
            free(ptr[i]);
            ptr[i] = NULL;
        }
        
        
    }
    }


     printf("The average time to execute Test 3 %f milliseconds\n", totalTimeThree/50);
  /*  
    // Test4
    for(int i = 0; i < 50; i++){
        gettimeofday(&startTime, 0);
        for(int j = 0; j < arraysize; j++){
            ptr[j] = malloc(rand()%3+1);
           // printf("Malloc %p\n", ptr[j]);
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
    
    printf("The average time to execute Test 4 %f milliseconds\n", totalTimeFour/50);


    // Test5

     
    unsigned int canmalloc = 1; // true 
    for(int i = 0; i < 50; i++){
        gettimeofday(&startTime, 0);
        
        int current = 1;
        int mallocIndex = 0;
        int freeIndex = 0;
        
        while(canmalloc != 0){

            if((ptr[mallocIndex] = malloc(50))){
                canmalloc = 0;
                continue;
            }

            printf("current %d\n", current);
            current++;
            mallocIndex++;
        }
            
        for(freeIndex = 0; freeIndex < mallocIndex; freeIndex+=2){
            printf("freeIndex %d", freeIndex);
            free(ptr[freeIndex]); 
            ptr[mallocIndex] = NULL;
        }
        for(mallocIndex = 0; mallocIndex < current-1; current+=2){
            ptr[mallocIndex] = malloc(35);
        }
        for(freeIndex = 0; freeIndex < current-1; freeIndex+=1){
            free(ptr[freeIndex]);
            ptr[freeIndex] = NULL;
        }
        gettimeofday(&endTime, 0);
        totalTimeFive = totalTimeFive + ((endTime.tv_sec-startTime.tv_sec)*1000000
        + (endTime.tv_usec-startTime.tv_usec));

        for(int i =0; i<arraysize;i++){

        if(ptr[i] != NULL){
            free(ptr[i]);
            ptr[i] = NULL;
        }
        
    }
    }
    

    
    
    printf("The average time to execute Test 5 %f milliseconds\n", totalTimeFive/50);

    

 */

    return 0;
}
