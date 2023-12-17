#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/stat.h>
#include "msgqueue.h"

int main(int argc, char *argv[]){

int queueid;
mymsg_t *mymsg;

queueid = msgget(KEY, PERM | IPC_CREAT);
if (queueid == -1){
   perror("Unable to get mssg");
   return 1;
}

if ((mymsg = (mymsg_t *)malloc(sizeof(mymsg_t))) == NULL){
	perror("Unavble to allcoate mem");
 	return 1;
 }
 
 msgrcv(queueid, mymsg, sizeof(mymsg_t), (long)atol(argv[1]), 0);
 printf("Message read is %s\n", mymsg->mtext);

}
