#include <stdio.h>
#include <stdlib.h>
#include "simple.h"

void print_reg_n_mem(int acc, int ir, int pc, int oc, int op, int mem[]);
int extract_sml(char filename[], int array[]);

int main(int argc, char *argv[])
{

    int accumulator, instruction_register, program_counter, opcode, operand;
    accumulator = instruction_register = program_counter = opcode = operand = 0;

    int memory[100];

    if (argc < 2)
    {
        printf("\n***SML FILE ARGUMENT MISSING***\n\n");
        return 0;
    }

    if (extract_sml(argv[1], memory))
    {
        return 0;
    }

    printf("\nINITIAL STATE OF MEMORY AND REGISTERS:\n");
    print_reg_n_mem(accumulator, instruction_register, program_counter, opcode, operand, memory);

    for (int i = 0; i < 100; i++)
    {
        instruction_register = memory[i];
        opcode = memory[i] / 100;
        operand = memory[i] % 100;
        program_counter = i;

        switch (opcode)
        {
        case READ:
        {
            printf("\n---READ INSTRUCTION---\n");
            printf("\nEnter a Number:\t\t\t");
            scanf("%d", &memory[operand]);
            break;
        }
        case WRITE:
        {
            printf("\n---WRITE INSTRUCTION---\n");
            printf("\nResult : \t\t\t%02d\n", memory[operand]);
            break;
        }
        case LOAD:
        {
            printf("\n---LOAD INSTRUCTION---\n");
            accumulator = memory[operand];
            break;
        }
        case STORE:
        {
            printf("\n---STORE INSTRUCTION---\n");
            memory[operand] = accumulator;
            break;
        }
        case ADD:
        {
            printf("\n---ADD INSTRUCTION---\n");
            accumulator = accumulator + memory[operand];
            break;
        }
        case SUBTRACT:
        {
            printf("\n---SUBTRACT INSTRUCTION---\n");
            accumulator = accumulator - memory[operand];
            break;
        }
        case DIVIDE:
        {
            printf("\n---DIVIDE INSTRUCTION---\n");
            if (memory[operand] == 0)
            {
                printf("\n***CANNOT DIVIDE BY ZERO***\n");
                break;
            }
            accumulator = accumulator / memory[operand];
            break;
        }
        case MULTIPLY:
        {
            printf("\n---MULTIPLY INSTRUCTION---\n");
            accumulator = accumulator * memory[operand];
            break;
        }
        case BRANCH:
        {
            printf("\n---BRANCH INSTRUCTION---\n");
            i = operand;
            break;
        }
        case BRANCHNEG:
        {
            printf("\n---BRANCHNEG INSTRUCTION---\n");
            if (accumulator < 0)
            {
                i = operand;
            }
            break;
        }
        case BRANCHZERO:
        {
            printf("\n---BRANCHZERO INSTRUCTION---\n");
            if (accumulator == 0)
            {
                i = operand;
            }
            break;
        }
        case HALT:
        {
            printf("\n---HALT INSTRUCTION---\n\n***PROGRAM HALTED***\n\nFINAL STATE OF MEMORY AND REGISTERS:\n");
            print_reg_n_mem(accumulator, instruction_register, program_counter, opcode, operand, memory);
            return 0;
        }
        default:
        {
            printf("\n***INVALID INSTRUCTION***\n\n");
            break;
        }
        }

        print_reg_n_mem(accumulator, instruction_register, program_counter + 1, opcode, operand, memory);
    }

    return 0;
}