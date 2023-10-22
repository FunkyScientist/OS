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
        while ((*counter) == 0)
        {
        }

        printf("\nIndex :\t%d\nSID :\t%d\nName :\t%s\n\n", *outptr, students[*outptr].SID, students[*outptr].name);

        *outptr = (*outptr + 1) % BUFSIZE;
        *counter = *counter - 1;

        if (students[*outptr].SID == -1)
        {
            break;
        }
    }

    shmctl(id, IPC_RMID, 0);

    return 0;
}
