#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int a = fork();

    if (a < 0)
    {
        printf("Error.");
    }
    else if (a == 0)
    {
        // int b=fork();
        // wait(NULL);
        printf("\nMe child hon. Return: %d", a);
        printf("\nProcess Id of child: %d", getpid());


       //printf("\nMe grand child hon. Return: %d", b);
    }
    else
    {
        wait(NULL);
        printf("\nMe parent hon. Return: %d\n", a);
        printf("Process Id of parent: %d", getpid());
    }
    // printf("\nProcess Id : %d", getpid());
    // printf("\nParent Process Id : %d", getppid());
    return 0;
}
