#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#define SEMKEY 222
union semun {
 int val;
 struct semid_ds *buf;
 unsigned short *array;
 struct seminfo *_buf;
};

void *thread_function(void *arg) {
// geting thread number from arg
 int *threadnum = (int *)arg;
 int p_number = *threadnum;
 
 struct sembuf sops[5];
 union semun argu;
 unsigned short chopsticks[5];
 
 int sem_id = semget(SEMKEY, 5, 0666);
 
srand(time(NULL));
while(1){
int timee = rand() % 5; // so that it must not wait for more than 5 seconds
sleep(timee);
printf("philospher # %d wants to eat\n", p_number);
argu.array = chopsticks;
if (semctl(sem_id, 0, GETALL, arg) == -1)
{
 perror("semctl error");
 exit(1);
}
//aquiring chopsticks before eating
sops[p_number-1].sem_num = p_number-1;
sops[p_number-1].sem_op = 0-1;
sops[p_number-1].sem_flg = 0;
sops[p_number].sem_num = p_number;
sops[p_number].sem_op = 0-1;
sops[p_number].sem_flg = 0;
if (semop(sem_id, sops, 5) < 0)
 perror("Semop error");
 else 
 printf("philospher # %d going to eat\n", p_number);
// eating for random amount of time

timee = rand() % 5;
sleep(timee);
if (semctl(sem_id, 0, GETALL, arg) == -1)
{
 perror("semctl error");
 exit(1);
}
// releasing chopsticks before saying done eating
sops[p_number-1].sem_num = p_number - 1;
sops[p_number-1].sem_op = 1;
sops[p_number-1].sem_flg = 0;
sops[p_number].sem_num = p_number;
sops[p_number].sem_op = 1;
sops[p_number].sem_flg = 0;
if (semop(sem_id, sops, 5) < 0)
 perror("Semop error");
 else 
 printf("philospher # %d done eating, now going to think\n", p_number);
} 
}
int main(){
 int sem_id; 

union semun arg;
 unsigned short chopsticks[5];
 sem_id = semget(SEMKEY, 5, (IPC_CREAT|IPC_EXCL|0666));
 if (sem_id < 0)
 perror ("Cannot create semaphore\n");
 else
 {
 // setting semaphores(chopsticks)
 for(int i=0;i<5;i++)
 chopsticks[i] = 1;
 
 arg.array = chopsticks;
 if (semctl(sem_id, 0, SETALL, arg) == -1)
 {
 perror("Error while setting semaphore");
 exit(1);
 }
 
 pthread_t thread[5];
 int threadnumber[5] = {1,2,3,4,5};
 // running threads
 pthread_create(&thread[0], NULL, thread_function, (void *)&threadnumber[0]);
 pthread_create(&thread[1], NULL, thread_function, (void *)&threadnumber[1]);
 pthread_create(&thread[2], NULL, thread_function, (void *)&threadnumber[2]);
 pthread_create(&thread[3], NULL, thread_function, (void *)&threadnumber[3]);
 pthread_create(&thread[4], NULL, thread_function, (void *)&threadnumber[4]);
 
 
 for(int i=0;i<5;i++){
 pthread_join(thread[i-1], NULL);
 } 
 }
}