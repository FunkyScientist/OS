#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

void *threadfunc(void *args){
	long t = (long)args;
	printf("Hello from Thread %ld.\n",t);
	pthread_exit(NULL);
	
}


int main(){
	pthread_t thread[NUM_THREADS];
	int err;
	long t;
	
	for(t=0 ; t<NUM_THREADS;t++){
	err = pthread_create(&thread[t],NULL,threadfunc,(void *)t);
    printf("%d",err);
	if(err){
		printf("UNABLE TO CREATE THREAD.\n");
		}
	}
	
	for(t=0 ; t<NUM_THREADS;t++){
	pthread_join(thread[t],NULL);
	}
	
	printf("ALL the Threads Completed.\n");
}