#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#define PERM (O_RDWR | O_CREAT )
int main(int argc, char *argv[]){
    pid_t pid;
    int fd[2];
    if (pipe(fd) == -1) {
        perror("Unable to create pipeline");
        return 1;
    }
    if ((pid = fork()) == -1) {
        perror("Unable to create child");
        return 1;
    }
    if (pid == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execl("/usr/bin/cat", "cat", argv[1], (char *)NULL);
        perror("execl for cat");
        exit(1);
    } else {
        close(fd[1]);
        int output_fd = creat(argv[2], 0644);
        if (output_fd == -1) {
            perror("open");
            exit(1);
        }
        dup2(fd[0], STDIN_FILENO);
        dup2(output_fd, STDOUT_FILENO);
        close(fd[0]);
        execl("/usr/bin/grep", "grep", "a", (char *)NULL);
        perror("execl for grep");
        exit(1);
    }
    return 0;
}

