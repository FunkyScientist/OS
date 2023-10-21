#include "header.h"

int main(int argc, char const *argv[])
{
    int shmid;

    void *shmem;

    shmid = shmget(KEY, SIZE, PERM | IPC_CREAT);

    shmem = shmat(shmid, NULL, 0);

    while (1)
    {
        printf("\nWrite Sumn : ");
        fgets(shmem, SIZE, stdin);

        if ((strncmp(shmem, "-1", 2)) == 0)
        {
            break;
        }
    }

    return 0;
}
