#include <stdio.h>
#include <stdlib.h>
#include "simple.h"

void display(int accum, int instCounter, int instReg, int opCode, int operand, int array[])
{
    printf("Accumulator : %d\n", accum);
    printf("Instruction Counter : %d\n", instCounter);
    printf("InstRegister : %d\n", instReg);
    printf("opCode : %d\n", opCode);
    printf("Operand : %d\n", operand);
    printf("\n");

    int i = 0;
    while (i < 100)
    {
        printf("%04d ", array[i]);
        if ((i + 1) % 10 == 0)
        {
            printf("\n");
        }

        i++;
    }

    printf("\n\n");
}

int main()
{
    int accum = 0;
    int instCounter = 0;
    int instReg;
    int opCode;
    int operand;
    int i = 0;
    int array[100];

    fileReading(array);

    i = 0;
    while (i < 100 && array[i] != 43)
    {
        instReg = array[i];
        instCounter = i;
        int store = array[i] / 100;
        opCode = store;
        int storee = array[i] % 100;
        operand = storee;

        switch (opCode)
        {
        case READ:
        {
            int o;
            printf("Enter the number : ");
            scanf("%d", &o);
            array[operand - 1] = o;

            display(accum, instCounter, instReg, opCode, operand, array);
            break;
        }
        case WRITE:
        {
            printf("The number is: %d at location %d\n", array[operand - 1], operand);
            display(accum, instCounter, instReg, opCode, operand, array);
            break;
        }
        case LOAD:
        {
            accum = array[operand - 1];
            display(accum, instCounter, instReg, opCode, operand, array);
            break;
        }
        case STORE:
        {
            array[operand - 1] = accum;
            display(accum, instCounter, instReg, opCode, operand, array);
            break;
        }
        case ADD:
        {
            accum = accum + array[operand - 1];
            display(accum, instCounter, instReg, opCode, operand, array);
            break;
        }
        case SUBTRACT:
        {
            accum = accum - array[operand - 1];
            display(accum, instCounter, instReg, opCode, operand, array);
            break;
        }
        case DIVIDE:
        {
            accum = accum / array[operand - 1];
            display(accum, instCounter, instReg, opCode, operand, array);
            break;
        }
        case MULTIPLY:
        {
            accum = accum * array[operand - 1];
            display(accum, instCounter, instReg, opCode, operand, array);
            break;
        }
        case BRANCH:
        {
            display(accum, instCounter, instReg, opCode, operand, array);
            break;
        }
        case BRANCHNEG:
        {
            instCounter = operand - 1;
            display(accum, instCounter, instReg, opCode, operand, array);
            break;
        }
        case BRANCHZERO:
        {
            if (accum < 0)
            {
                instCounter = operand - 1;
            }
            display(accum, instCounter, instReg, opCode, operand, array);
            break;
        }
        case HALT:
        {
            display(accum, instCounter, instReg, opCode, operand, array);
            exit(0);
            printf("Exit..........");

            break;
        }
        }

        i++;
    }
    return 0;
}
