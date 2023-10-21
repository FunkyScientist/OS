#include <stdio.h>
#include <stdlib.h>

void display(int acc, int insCounter, int insReg, int opCode, int operand)
{
    printf("\nAccumulator: %d", acc);
    printf("\nInstruction Counter: %d", insCounter);
    printf("\nInstruction Register: %d", insReg);
    printf("\nOpcode: %d", opCode);
    printf("\nOperand: %d\n\n", operand);
}

void table(int array[])
{
    for (int i = 0; i < 100; i++)
    {
        // array[i] = 0;
        printf("%04d ", array[i]);
        if ((i + 1) % 10 == 0)
        {
            printf("\n");
        }
    }
}

void readFile(int array[], const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }

    int i = 0;
    while (i < 100 && fscanf(file, "%d", &array[i]) != EOF)
    {
        i++;
    }

    fclose(file);
}