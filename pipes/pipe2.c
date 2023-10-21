#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{

    int fd[2];
    if (pipe(fd) == -1)
    {
        printf("\nERROR.\n");
    }

    int id = fork();

    if (id == -1)
    {
        printf("\nFORK FAILED.\n");
    }

    if (id == 0)
    {
        close(fd[0]);
        int a;
        printf("\nENTER THE NUMBER : ");
        scanf("%d", &a);
        write(fd[1], &a, sizeof(int));
        close(fd[1]);
    }
    else
    {
        wait(NULL);
        close(fd[1]);
        int b;
        read(fd[0], &b, sizeof(int));
        close(fd[0]);
        printf("\nTHE SQUARE IS : %d\n\n", b * b);
    }

    return 0;
}
