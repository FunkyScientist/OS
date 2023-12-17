#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#define BUFFER_SIZE PIPE_BUF

int main(int argc, char* argv[]){

  int res, pipe_fd, char_count;
  time_t cur_time;
  char buffer[BUFFER_SIZE+1];
  
  
  printf("\nProcess %d going to open %s for writing\n", getpid(), argv[1]);
  if((pipe_fd = open(argv[1], O_WRONLY)) == -1){
  
    perror("Unable to open pipe");
    return 1;
    
  }
  while(1){
  
    cur_time = time(NULL);
    char_count = sprintf(buffer, "\nProcess %d says AoA, time is : %s welcome to OS\n", getpid(), ctime(&cur_time));
  
    if((res = write(pipe_fd, buffer, char_count)) == -1){
    
      perror("Unable to write to pipe");
      return 1;
    
    }
    
    sleep(1);
  }

  close(pipe_fd);
  
  
  return 0;
}


  
