#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int i, n, j;

void *thread_function(void *arg)
{
    n = atoi(arg);

    for (i = 0; i < n; i++)
    {
        printf("%d\n", i);
    }
    pthread_exit("Done"); // Thread returns "Done"
}

int main()
{
    char *m = "5";

    pthread_t a_thread; // thread declaration
    void *result;

    pthread_create(&a_thread, NULL, thread_function, (void *)m); // thread is created
    pthread_join(a_thread, &result);

    printf("Thread joined\n");

    for (j = 20; j < 25; j++)
    {
        printf("%d\n", j);
    }

    printf("thread returned %s\n", (char *)result);
}