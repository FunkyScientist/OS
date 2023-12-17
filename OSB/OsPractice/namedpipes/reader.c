#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int arr[5];

    int rFile = open("sum", O_RDONLY);
    if (rFile == -1)
    {
        return 1;
    }

    for (int i = 0; i < 5; i++)
    {
        if (read(rFile, &arr[i], sizeof(int)) == -1)
        {
            return 2;
        }
        printf("%d\n", arr[i]);
    }
    
    int total;

    read(rFile, &total, sizeof(int));
    close(rFile);

    printf("SUM: %d", total );
    return 0;
}
