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
    int i;

    for (i = 0; i < 5; i++)
    {
        arr[i] = rand() % 10;
    }

    mkfifo("sum", 0777);

    int wFile = open("sum", O_WRONLY | O_CREAT);
    printf("File opened.\n");

    if (wFile == -1)
    {
        printf("Error.");
        return 1;
    }

    int total = 0;

    for (int i = 0; i < 5; i++)
    {
        if (write(wFile, &arr[i], sizeof(int)) == -1)
        {
            return 2;
        }
        printf("%d\n", arr[i]);
        total += arr[i];
    }
    //printf("Sum: %d", total);
    write(wFile, &total, sizeof(int));     

    close(wFile);

    return 0;
}
