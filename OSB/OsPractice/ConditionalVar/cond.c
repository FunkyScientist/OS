#include <errno.h>
#include <pthread.h>
#include <stdio.h>

pthread_cond_t bcond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t bmutex = PTHREAD_MUTEX_INITIALIZER;

int count = 0;
int limit = 3;

int waitbarrier(void)
{
    /* wait at the barrier until all n threads arrive */
    int berror = 0;
    int error;

    if (error = pthread_mutex_lock(&bmutex))
        return error;

    count++;

    while ((count < limit))
        berror = pthread_cond_wait(&bcond, &bmutex);

    if (!berror)
        berror = pthread_cond_broadcast(&bcond);

    error = pthread_mutex_unlock(&bmutex);

    if (berror)
        return berror;

    return error;
}

static void *printpthread(void *arg)
{
    fprintf(stderr, "This is the first print of thread %d\n", (int)pthread_self());
    waitbarrier();
    fprintf(stderr, "This is the second print of thread %d\n", (int)pthread_self());
    return NULL;
}

int main(void)
{
    pthread_t t0, t1, t2;

    if (pthread_create(&t0, NULL, printpthread, NULL))
        fprintf(stderr, "Error creating thread 0");

    if (pthread_create(&t1, NULL, printpthread, NULL))
        fprintf(stderr, "Error creating thread 1");

    if (pthread_create(&t2, NULL, printpthread, NULL))
        fprintf(stderr, "Error creating thread 2");

    if (pthread_join(t0, NULL))
        fprintf(stderr, "Error joining thread 0");

    if (pthread_join(t1, NULL))
        fprintf(stderr, "Error joining thread 1");

    if (pthread_join(t2, NULL))
        fprintf(stderr, "Error joining thread 2");

    fprintf(stderr, "All threads complete\n");
}

