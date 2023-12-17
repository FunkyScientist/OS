#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* my_func(void *arg)
{
    printf("\nIN THREAD %s.", (char*) arg);
    int n = *((int*)arg);

    for (int i = 0; i < n; i++)
    {
        printf("\n%d", i);
    }
    pthread_exit("Done");
}

int main(int argc, char const *argv[])
{
    int m = 5;
    pthread_t t1, t2;
    void *result;

    //pthread_create(&t1, NULL, &my_func, "T1");
    pthread_create(&t1, NULL, &my_func,(void*) &m);
    //pthread_create(&t2, NULL, &my_func,(void*) "T2");

    pthread_join(t1, &result);
   // pthread_join(t2, NULL);

    printf("\nThread execution %s\n", (char*)result);
    
    printf("Main func\n");
    for (int j = 20; j < 25; j++)
    {
        printf("%d\n", j);
    }
    
    return 0;
}
