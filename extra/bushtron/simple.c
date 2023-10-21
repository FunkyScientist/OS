#include <stdio.h>
#include <stdlib.h>
#include "simple.h"

void display(int acc, int insCounter, int insReg, int opCode, int operand);
void readFile(int array[], const char *filename);
void table(int array[]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <SML filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1]; // Get the SML filename from command line
    int acc = 0;
    int insCounter = 0;
    int insReg;
    int opCode;
    int operand;
    int array[100];

    for (int i = 0; i < 100; i++)
    {
        array[i] = 0;
    }

    display(acc, insCounter, insReg, opCode, operand);
    readFile(array, filename); // Pass the filename to the readFile function
    table(array);

    int i = 0;
    while (i < 100 && array[i] != HALT)
    {
        insReg = array[i];


        insCounter = i;
        int store = array[i] / 100;
        opCode = store;
        int storee = array[i] % 100;
        operand = storee;

        switch (opCode)
        {
        case READ:
        {
            int o;
            printf("\n\nEnter the number : ");
            scanf("%d", &o);
            array[operand ] = o;

            display(acc, insCounter+1, insReg, opCode, operand);
            table(array);
            break;
        }
        case WRITE:
        {
            printf("The number is: %d at location %d\n", array[operand - 1], operand);
            display(acc, insCounter+1, insReg, opCode, operand);
            table(array);
            break;
        }
        case LOAD:
        {
            acc = array[operand ];
            display(acc, insCounter+1, insReg, opCode, operand);
            table(array);
            break;
        }
        case STORE:
        {
            array[operand ] = acc;
            display(acc, insCounter+1, insReg, opCode, operand);
            table(array);
            break;
        }
        case ADD:
        {
            acc = acc + array[operand ];
            display(acc, insCounter+1, insReg, opCode, operand);
            table(array);
            break;
        }
        case SUBTRACT:
        {
            acc = acc - array[operand ];
            display(acc, insCounter+1, insReg, opCode, operand);
            table(array);
            break;
        }
        case DIVIDE:
        {
            acc = acc / array[operand ];
            display(acc, insCounter+1, insReg, opCode, operand);
            table(array);
            break;
        }
        case MULTIPLY:
        {
            acc = acc * array[operand ];
            display(acc, insCounter+1, insReg, opCode, operand);
            table(array);
            break;
        }

        case BRANCH:
        {
            insCounter = operand ;
            display(acc, insCounter+1, insReg, opCode, operand);
            break;
        }
        case BRANCHNEG:
        {
            if (acc < 0)
            {
                insCounter = operand ;
            }
            display(acc, insCounter+1, insReg, opCode, operand);
            break;
        }
        case BRANCHZERO:
        {
            if (acc == 0)
            {
                insCounter = operand ;
            }
            display(acc, insCounter+1, insReg, opCode, operand);
            break;
        }
        case HALT:
        {
            exit(0);
            printf("Exit..........\n");

            break;
        }
        }

        i++;
    }
    return 0;
}