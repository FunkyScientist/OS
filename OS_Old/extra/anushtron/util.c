#include <stdio.h>
#include <stdlib.h>
#include "simple.h"

void smlTxt_Into_RAM(int array[],const char *fileName) {

    for (int i = 0; i < 100; i++){
    array[i] =0;
    }
    FILE* file; 
    file = fopen(fileName, "r");
    if (file != NULL) {
        int i = 0;
        while (i < SIZE && fscanf(file, "%d", &array[i]) == 1) {
            
           i++;
        }
        fclose(file);
    } else {
        printf("SMl File is empty or not found \n");
    }
}
