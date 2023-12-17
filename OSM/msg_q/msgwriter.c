#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys//msg.h>
#include <unistd.h>
#include <sys/stat.h>
#include "msgqueue.h"

int main(int argc, char *argv[]){

  int queueid;
  mymsg_t *mymsg;
  queueid = msgget(KEY , PERM | IPC_CREAT);
  if(queueid == -1){
 perror("unable to getmsgqueue");
 return 1;
 }
 
 if((mymsg = (mymsg_t *)malloc(sizeof(mymsg_t))) == NULL){
  	perror("Unable to aloocate mem");
   	return 1;
   }
   
   sprintf(mymsg->mtext, "this message was written by %ld\n", (long)getpid());
   mymsg->mtype = atoi(argv[1]);
   if(msgsnd(queueid, mymsg, sizeof(mymsg_t), 0)  == -1){
   	perror("Unable to send msg");
   	return 1;
  }
}




