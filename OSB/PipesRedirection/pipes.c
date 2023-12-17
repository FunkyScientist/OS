#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{

    int fd[2];

    if (pipe(fd) == -1)
    {
        printf("Error.");
    }

    int id = fork();

    if (id == 0)
    {
        int a;
        int b;
        close(fd[0]);
        printf("Enter a number: ");
        scanf("%d", &a);
        b = a * a;
        write(fd[1], &b, sizeof(int));
        close(fd[1]);
    }
    else
    {
        wait(NULL);
        int c;
        close(fd[1]);
        read(fd[0], &c, sizeof(int));
        close(fd[0]);

        for (int i = 1; i <= 10; i++)
        {
            printf("\n%d x %d = %d", c, i, c * i);
        }
    }

    return 0;
}