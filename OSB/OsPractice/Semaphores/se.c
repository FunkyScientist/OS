#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

sem_t s;
int shared = 1;

void *func1(void* args)
{
    sem_wait(&s);
    int x = shared;
    printf("\nReads %d", x);
    x++;
    printf("\nAfter x++: %d", x);
    sleep(1);
    shared = x;
    printf("\nFinal value of t1: %d", shared);
    sem_post(&s);
}

void *func2(void* args)
{
    sem_wait(&s);
    int y = shared;
    printf("\nReads %d", y);
    y--;
    printf("\nAfter y--: %d", y);
    sleep(1);
    shared = y;
    printf("\nFinal value of t2: %d", shared);
    sem_post(&s);
}

int main(int argc, char const *argv[])
{
     sem_init(&s, 0, 1);
    pthread_t t1, t2;

    pthread_create(&t1, NULL, &func1, NULL);
    pthread_create(&t2, NULL, &func2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("\nFinal value of shared is %d\n", shared);
    return 0;
}
