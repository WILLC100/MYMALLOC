     
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "mymalloc.h"



int main(int argc, char* argv[] ){ // runs program here 

    //must initialize first metadata node with byte manipulation 

     FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Test File cannot be opened.");
        exit(EXIT_FAILURE);
    }
/*
    unsigned int count;
    fscanf(fp, "%d", &count);
    char* test1 =NULL;
    
    unsigned int wack = 0;

    char** test1arr = malloc(sizeof(char*)*count);

    for(int i =0; i<count; i++ ){

        test1 = malloc(1);

        test1arr[i] = test1;
        
        printf("%p ", test1arr[i]);

        if((i+1)%6 == 0){         
            printf("Line %d", wack);
            printf("\n");
            wack = wack+1;
        }
    }
    for(int i=0; i<count;i++){
        free(test1arr[i]);
    }
    free(test1arr);
 */

    //test 1

    int* ptr[1000];
    struct timeval startTime; 
    struct timeval endTime; 
    float totalTimeB = 0;
    for(int i =0; i<100; i++){
        gettimeofday(&startTime, NULL);
        for(int j=0; j<120; j++){
            
            ptr[j] = (int*)malloc(1);
            free(ptr[j]);
            ptr[j] = NULL;
        }
        gettimeofday(&endTime, NULL);
        //printf("%ld\n", endTime.tv_sec);
        totalTimeB = totalTimeB + ((endTime.tv_sec - startTime.tv_sec)*1000000
         + (endTime.tv_usec - startTime.tv_usec));

    }
    printf("The mean time to execute Test 1 %f microseconds\n", totalTimeB/100);


    fclose(fp);

    return 0; 

}