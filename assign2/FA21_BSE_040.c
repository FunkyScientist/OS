#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        printf("\nTOO FEW ARGUMENTS.\nUSAGE : %s <input_file> <output_file>\n", argv[0]);
        return 0;
    }

    int fd[2];

    if (pipe(fd) == -1)
    {
        printf("\nPIPE ERROR\n");
        return 1;
    }

    int id = fork();

    if (id == -1)
    {
        printf("\nFORK ERROR\n");
        return 1;
    }

    if (id == 0)
    {
        close(fd[0]);

        int input_file = open(argv[1], O_RDONLY);

        if (input_file == -1)
        {
            printf("\nINPUT FILE ERROR.\n");
            return 1;
        }

        dup2(input_file, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);

        close(fd[1]);
        close(input_file);

        execl("/usr/bin/cat", "cat", NULL);
        printf("\nEXEC ERROR\n");
    }
    else
    {
        wait(NULL);

        close(fd[1]);

        int output_file = creat(argv[2], 0600);

        if (output_file == -1)
        {
            printf("\nOUTPUT FILE ERROR.\n");
            return 1;
        }

        dup2(fd[0], STDIN_FILENO);
        dup2(output_file, STDOUT_FILENO);

        close(fd[0]);
        close(output_file);

        execl("/usr/bin/grep", "grep", "x", NULL);
        printf("\nEXEC ERROR\n");
    }

    return 0;
}
