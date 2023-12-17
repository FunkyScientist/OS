#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    /* fork a child process */
    pid = fork();
    if (pid < 0)
    {
        /* error occurred */
        fprintf(stderr, "\nFork Failed\n");
        return 1;
    }
    else if (pid != 0)
    {
        /* parent process */
        /* parent will wait for the child to complete */
        wait(NULL);
        printf("\nChild Complete\n\n");
    }
    else if (pid == 0)
    {
        /* child process */
        execlp("/usr/bin/cmatrix", "cmatrix", NULL);
    }
    return 0;
}