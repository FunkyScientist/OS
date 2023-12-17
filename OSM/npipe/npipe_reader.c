#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define BUFFER_SIZE PIPE_BUF
int main(int argc, char *argv[]){
int res,pipe_fd;
char buffer[BUFFER_SIZE+1];
memset(buffer, '\0', sizeof(buffer));
printf("Process %d going tp open %s for reading\n", getpid(), argv[1]);
if((pipe_fd=open (argv[1], O_RDONLY))==-1){
perror("Unable to open pipe");
return 1;
}
while(1){
if((res =read (pipe_fd, buffer, BUFFER_SIZE))==-1){
perror("unable to read from file");
return 1;
}
fprintf(stderr, "message read from pipe: %s \n",buffer);
memset(buffer,'\0', sizeof(buffer));
sleep(1);
}
close(pipe_fd);
}
