     
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "mymalloc.h"



int main(int argc, char* argv[] ){ // runs program here 

    int *ptr[1000];
    struct timeval startTime;
    struct timeval endTime;
    float totalTimeOne = 0;
    float totalTimeTwo = 0;
   // int totalTimeThree = 0;
   // int totalTimeFour = 0;
    
    //Test1
    for(int i = 0; i < 50; i++){
        gettimeofday(&startTime, 0);
        for(int j = 0; j < 120; j++){
            ptr[j] = (int*)(malloc(1));
          
           
            free(ptr[j]);
            ptr[j] = NULL;
        }
        gettimeofday(&endTime, 0);
        totalTimeOne = totalTimeOne + ((endTime.tv_sec-startTime.tv_sec)*1000000 
        + (endTime.tv_usec-startTime.tv_usec));
    }

    printf("The average time to execute Test 1 %f milliseconds\n", totalTimeOne/50);
    
    //Test2
    for(int i = 0; i < 50; i++){
        gettimeofday(&startTime, 0);
        for(int j = 0; j < 120; j++){
            ptr[j] = (int *) malloc(1);
          //  printf("%d %p \n", j, ptr[j]); last allocation from 76 onwards DNE
        }
        
        for(int g = 0; g < 120; g++){
         //   printf("%d %p \n", i, ptr[g]); // round 84, test 76. 
            free(ptr[g]);
            ptr[g] = NULL;
        }
        gettimeofday(&endTime, 0);
        totalTimeTwo = totalTimeTwo + ((endTime.tv_sec-startTime.tv_sec)*1000000
        + (endTime.tv_usec-startTime.tv_usec));
    }
    
  
    printf("The average time to execute Test 2 %f milliseconds\n", totalTimeTwo/50);

    return EXIT_SUCCESS;
}