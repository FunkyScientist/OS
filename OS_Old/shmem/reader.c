#include "header.h"

int main(int argc, char const *argv[])
{
    int shmid;

    void *shmem;

    shmid = shmget(KEY, SIZE, PERM);

    shmem = shmat(shmid, NULL, 0);

    while (1)
    {

        printf("\nRECEIVED : %s", (char *)shmem);

        if ((strncmp(shmem, "-1", 2)) == 0)
        {
            break;
        }
    }

    shmctl(shmid, IPC_RMID, 0);

    return 0;
}
