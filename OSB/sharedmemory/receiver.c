#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    void* shared_memory;
    char buff[100];

    int shmid = shmget((key_t)153, 1024, 0666);
    printf("Key is: %d", shmid);

    shared_memory = shmat(shmid, NULL, 0); //receiver process attached to shared mem
    printf("\nProcess attached at %p", shared_memory);
    printf("\nData is: %s", (char*)shared_memory);
    return 0;
}
