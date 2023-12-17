#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int childpid = 0; // store the process ID of the processes
    int i;
    int n = atoi(argv[1]); // convert string to int

    if (argc != 2)
    {
        printf("Cmd args error.");
    }

    for (i = 1; i < n; i++)
    {
        if (childpid = fork())
        {
            break;
        }
    }

    fprintf(stderr, "i:%d  process ID:%d  parent ID:%d  child ID:%d\n", i, getpid(), getppid(), childpid);

    return 0;
}
