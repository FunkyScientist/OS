#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char const *argv[])
{

    srand(time(NULL));

    int size = atoi(argv[1]);

    int arr[size];

    mkfifo("sum", 0600);

    int fd = open("sum", O_WRONLY);

    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 10;
        write(fd, &arr[i], sizeof(int));
        printf("Wrote %d hehe.\n", arr[i]);
    }

    close(fd);

    return 0;
}
