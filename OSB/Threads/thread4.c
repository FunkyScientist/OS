#include <stdio.h>
#include <pthread.h>

struct arg_struct
{ // structure which contains multiple variables that are to passed as input to the thread
    int arg1;
    int arg2;
};

void *arguments(void *arguments)
{
    struct arg_struct *args = arguments;
    printf("%d\n", args->arg1);
    printf("%d\n", args->arg2);
    pthread_exit(NULL);
}

int main()
{
    pthread_t t;
    struct arg_struct args;
    
    args.arg1 = 5;
    args.arg2 = 7;
    pthread_create(&t, NULL, arguments, &args);
    // structure passed as 4th argument
    pthread_join(t, NULL); /* Wait until thread is finished */
}