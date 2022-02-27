     
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


    int wack = 1; 
    wack = wack +2;

}