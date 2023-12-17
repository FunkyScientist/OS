#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#define BUFFER_SIZE PIPE_BUF
int main(int argc, char *argv[]){
int res,pipe_fd,char_count;
char buffer[BUFFER_SIZE+1];
printf("Process %d going tp open %s for reading\n", getpid(), argv[1]);
if((pipe_fd=open (argv[1], O_WRONLY))==-1){
perror("Unable to open pipe");
return 1;
}														
while(1){
time_t cur_time =time(NULL);
char_count=sprintf(buffer,"Process %d says AOA, time is: %s welcome to OS\n", getpid(), ctime(&cur_time));
if((res =write (pipe_fd, buffer, BUFFER_SIZE))==-1){
perror("unable to write from file");
return 1;
}
sleep(1);
}
close(pipe_fd);
}
