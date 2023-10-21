#include <stdio.h>
#include <stdlib.h>

void print_reg_n_mem(int acc, int ir, int pc, int oc, int op, int mem[])
{
    int location;

    printf("\nAccumulator : \t\t\t%02d", acc);
    printf("\nProgram Counter : \t\t%02d", pc);
    printf("\nInstruction Register : \t\t%04d", ir);
    printf("\nOperation Code : \t\t%02d", oc);
    printf("\nOperand : \t\t\t%02d\n", op);
    printf("\nMEMORY :\n\n");

    for (int i = 0; i < 10; i++)
    {
        printf("\t%02d", i);
    }

    printf("\n\n");

    for (int i = 0; i < 10; i++)
    {
        printf("%02d", i);

        for (int j = 0; j < 10; j++)
        {
            location = (i * 10) + j;
            printf("\t%04d", mem[location]);
        }

        printf("\n");
    }

    printf("\n\n------------------------------------------------------------------------------------\n");
}

int extract_sml(char filename[], int array[])
{

    for (int i = 0; i < 100; i++)
    {
        array[i] = 0;
    }

    FILE *sml;
    sml = fopen(filename, "r");
    if (sml != NULL)
    {
        for (int i = 0; i < 100; i++)
        {
            if (fscanf(sml, "%d", &array[i]) == EOF)
                break;
        }

        fclose(sml);
        return 0;
    }
    else
    {
        printf("\n***SML FILE ERROR***\n\n");
        return 1;
    }
}