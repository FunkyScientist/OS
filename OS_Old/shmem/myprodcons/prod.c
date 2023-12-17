#include "header.h"

int main(int argc, char const *argv[])
{
    int id;
    char *cptr;
    int *inptr, *outptr, *counter;

    student *students;

    if ((id = shmget(KEY, SIZE, PERM)) == -1)
    {
        perr();
    }

    if ((cptr = (char *)shmat(id, NULL, 0)) == (void *)-1)
    {
        perr();
    }

    inptr = (int *)cptr;
    outptr = (int *)cptr + 4;
    counter = (int *)cptr + 8;
    students = (student *)cptr + 12;

    *inptr = 0;
    *outptr = 0;
    *counter = 0;

    while (1)
    {
        while ((*counter) == BUFSIZE)
        {
        }

        printf("\nEnter Student ID Number: ");
        scanf("%d", &students[*inptr].SID);

        printf("\nEnter Name: ");
        scanf("%s", students[*inptr].name);

        // write(STDOUT_FILENO, "\nEnter Name: ", 13);
        // read(STDIN_FILENO, students[*inptr].name, SIZE);

        printf("\nWrote at: %d\n", *inptr);

        if (students[*inptr].SID == -1)
        {
            *inptr = (*inptr + 1) % BUFSIZE;
            *counter = *counter + 1;
            break;
        }

        *inptr = (*inptr + 1) % BUFSIZE;
        *counter = *counter + 1;
    }

    return 0;
}
