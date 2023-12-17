#include"myheader.h"
int main(){
int sem_id;
union semun arg;
unsigned short dcount[3];
sem_id=semget(SEMKEY,3, (IPC_CREAT|IPC_EXCL|0666));
if(sem_id<0)
perror("Cannot create Semaphore");
else{
dcount[PLAIN]=3;
dcount[CHOC]=4;
dcount[SHUG]=5;
arg.array=dcount;
if(semctl(sem_id,0, SETALL,arg)==-1){
perror("semctl");
exit(1);
}
}
return 0;
}
