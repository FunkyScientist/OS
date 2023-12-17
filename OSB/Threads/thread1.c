#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int i, j, n;

void* thread_func(void *args)
{
    printf("Inside Thread\n");
    
    for (int i = 0; i < 5; i++)
    {
        printf("%d\n",i);
    }
    
}

int main(int argc, char const *argv[])
{
    pthread_t t;
    pthread_create(&t, NULL, thread_func, NULL); //2. attributes of thread, 4.input to thread func
    pthread_join(t, NULL); //makes main process wait for thread to finish

    printf("Inside main\n");

    for (int j = 20; j < 25; j++)
    {
       printf("%d\n", j);
    }
    
    return 0;
}
