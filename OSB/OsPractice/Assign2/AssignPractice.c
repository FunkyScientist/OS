#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int fd[2];

    if(pipe(fd) == -1){
        printf("Error creating a pipe.");
    }

    int a = fork();

    if (a == -1)
    {
        printf("Error creating fork");
    }
    else if (a == 0)
    {
        
        int inp = open(argv[1], O_RDONLY);
        dup2(inp, STDIN_FILENO);   //reads file from stdin which is redirecting to inp file so it will read from inp file
        dup2(fd[1], STDOUT_FILENO); //cat prints on stdout & it is redirecting to pipe 
        close(fd[0]);
        close(inp);
        execl("/usr/bin/cat", "cat", NULL);

    }else
    {
        wait(NULL);
        
        int op = creat(argv[2], 0600);
        dup2(fd[0], STDIN_FILENO); //stdin stores input file 
        dup2(op, STDOUT_FILENO);
        close(fd[1]);
        close(op);
        execl("/usr/bin/grep", "grep", "x", NULL);
    }
    
    return 0;
}
