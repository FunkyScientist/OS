#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    void *shared_memory; //store or print the address where shared segment gets attached to process address space 
    char buff[100]; //gets data from user
    
    int shmid = shmget((key_t)153, 1024, 0666 | IPC_CREAT); //1024 is size of segment
    printf("Key of Shared Memory is %d\n", shmid);

    shared_memory = shmat(shmid, NULL, 0); //attach shared segment to address of sender process
    //shmat returns address where segment gets attached to process
    printf("Process attached to %p\n", shared_memory);

    printf("\nEnter data to shared memory\n");
    read(0, buff, 100);  //read from keyboard into the buffer, max 100 char

    strcpy(shared_memory, buff);
    printf("\nYou wrote %s", (char*)shared_memory);

    return 0;
}