#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int childpid =0;

    int i;
    int n = atoi(argv[1]);

    for ( i = 0; i < n; i++)
    {
        if((childpid = fork()) <= 0){
            break;
        }
    }
    wait(NULL);
    printf("i:%d  process ID:%d  parent ID:%d  child ID:%d\n", i, getpid(), getppid(), childpid);
    
    return 0;
}
