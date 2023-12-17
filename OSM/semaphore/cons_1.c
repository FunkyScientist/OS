#include "myheader.h"
int sem_id;
struct sembuf sops[3];
int main(void){

union semun arg;
unsigned short dcount[3];
sem_id=semget(SEMKEY, 3, 0666);
if(sem_id<0)
perror("Cannot get semaphore");
else{
arg.array=dcount;
if(semctl(sem_id,0,GETALL,arg)==-1){
perror("semctl");
exit(1);

}
printf("Plain: %d, Chocolate:%d, Sugar: %d", arg.array[PLAIN], arg.array[CHOC], arg.array[SHUG]);
printf("Enter how many plain, chocolate and Sugar donuts you want to produce");
scanf("%hu %hu %hu",&arg.array[PLAIN],&arg.array[CHOC],&arg.array[SHUG]);
sops[PLAIN].sem_num=PLAIN;
sops[PLAIN].sem_op=0-arg.array[PLAIN];
sops[PLAIN].sem_flg=0;
sops[SHUG].sem_num=SHUG;
sops[SHUG].sem_op=0-arg.array[SHUG];
sops[SHUG].sem_flg=0;
sops[CHOC].sem_num=CHOC;
sops[CHOC].sem_op=0-arg.array[CHOC];
sops[CHOC].sem_flg=0;
if(semop(sem_id,sops,3)<0)
perror("SEMOP ERROR");
else
semctl(sem_id,0,GETALL, arg);
printf("new values are PLain:%d, Sugar:%d, Chocolate:%d", arg.array[PLAIN], arg.array[SHUG], arg.array[CHOC]);
}
return 0;
}
