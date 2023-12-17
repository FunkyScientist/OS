#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PERM (0_RDWR | 0_CREAT)

int main(int argc, char *argv[])
{
    char out_msg[] = "\nThis message is suppossed to appear on stdout\n";
    char err_msg[] = "\nThis message is suppossed to appear on stderr\n";
    printf("Simple printf for the first time\n");

    if (atoi(argv[3]) == 1)
    {
        int out_fd, err_fd;
        out_fd = creat(argv[1], 0600);
        err_fd = creat(argv[2], 0600);
        dup2(out_fd, STDOUT_FILENO);
        dup2(err_fd, STDERR_FILENO);
    }

    printf("Simple printf for the second time\n");
    write(STDOUT_FILENO, out_msg, strlen(out_msg));
    write(STDERR_FILENO, err_msg, strlen(err_msg));

    return 0;
}
