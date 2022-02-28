     
#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"



int main(int argc, char* argv[] ){ // runs program here 

    //must initialize first metadata node with byte manipulation 

     FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("File cannot be opened.");
        exit(EXIT_FAILURE);
    }

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
 

    fclose(fp);

}