#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int fd[2];

    if (pipe(fd) == -1)
    {
        printf("Error.");
        return 1;
    }

    int a = fork();

    if (a == -1)
    {
        printf("Error.");
        return 1;
    }
    else if (a == 0)
    {

        int inFile = open(argv[1], O_RDONLY);
        dup2(inFile, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        
        close(fd[0]);
        close(inFile);

        execl("/usr/bin/cat", "cat", NULL);
       
    }
    else
    {
        
        wait(NULL);
        int outFile = creat(argv[2], 0600);
        dup2(fd[0], STDIN_FILENO);
        dup2(outFile, STDOUT_FILENO);

        close(fd[1]);
        close(outFile);

        execl("/usr/bin/grep", "grep", "x", NULL);
        
    }

    return 0;
}
