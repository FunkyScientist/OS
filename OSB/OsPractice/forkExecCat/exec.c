#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int a = fork();

    if (a < 0)
    {
        printf("Error.");
    }
    else if (a == 0)
    {
        printf("\nMe child hon. Return: %d\n", a);
        printf("\nProcess Id of child: %d\n", getpid());
        execl("/usr/bin/nano","nano", "notes.txt", NULL);
    }
    else
    {
        wait(NULL);
        
        printf("\nMe parent hon. %d\n", a);
        printf("\nProcess Id of parent: %d\n", getpid());

        execl("/usr/bin/ls", "ls", "-la", NULL);
    }
    //printf("\nProcess Id : %d", getpid());
    //printf("\nParent Process Id : %d", getppid());
    return 0;
}


