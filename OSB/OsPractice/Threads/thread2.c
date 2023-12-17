#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int num[] = {3,5};

void *thread_func(void* arg)
{
    printf("Inside Thread\n");
    int *x = arg;
    int sum = x[0] + x[1];

    printf("Sum is %d\n", sum);
    pthread_exit("Sum calculated.\n"); //return of thread back to main
}


int main(int argc, char const *argv[])
{
    pthread_t t;
    void *result;

    pthread_create(&t, NULL, thread_func, (void *)num ); //passing num array to thread func
    pthread_join(t, &result); 

    printf("Inside main process\n");
    printf("Thread Returned: %s\n", (char *)result);

    return 0;
}