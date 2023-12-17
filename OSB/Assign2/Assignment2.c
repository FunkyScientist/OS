#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int inFile = open("Input.txt", O_RDONLY);
    int outFile = creat("Output.txt", 0600);

    //char d[] = {"HELLO WORLD."};

    //write(outFile, &d, sizeof(d)-1);

   // close(outFile);

    if (outFile == -1)
    {
        printf("Error.");
    }

    int fd[2];

    if (pipe(fd) == -1)
    {
        printf("Error.");
    }

    int a = fork();

    if (a == -1)
    {
        printf("Error.");
    }
    else if (a == 0)
    {
        char b[100];
        //close(fd[1]);
        read(inFile, &b, sizeof(b));
        dup2(inFile, STDIN_FILENO);
        close(fd[0]);
        dup2(outFile, STDOUT_FILENO);
        execl("/usr/bin/grep", "grep", "x", NULL);
        //write(outFile, &d, sizeof(d)-1);
        //close(fd[1]);
    }
    else
    {
        wait(NULL);
        int c;
        close(fd[1]);
        read(inFile, &c, sizeof(c));
        dup2(inFile, STDIN_FILENO);
        execl("/usr/bin/cat", "cat", NULL);
    }
    return 0;
}
