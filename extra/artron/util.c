#include <stdio.h>
#include "simple.h"
void fileReading(int array[])
{

    int i = 0;
    FILE *file;

    file = fopen("./Instructions.txt", "r");

    if (file == NULL)
    {
        printf("There are no instructions\n");
    }
    else
    {

        for (int j = 0; j < 100; j++)
        {
            array[j] = 0;
        }
    }

    while (i < 100)
    {
        if (fscanf(file, "%d", &array[i]) == EOF)
        {
            break;
        }
        i++;
    }

    fclose(file);
}
