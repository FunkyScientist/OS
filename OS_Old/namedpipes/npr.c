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
    int size = atoi(argv[1]);
    int arr[size];

    int fd = open("sum", O_RDONLY);
    int totalsum = 0;

    for (int i = 0; i < size; i++)
    {
        read(fd, &arr[i], sizeof(int));
        printf("\nRead %d hehe.", arr[i]);
        totalsum += arr[i];
    }

    close(fd);

    printf("\n\nSUM IS %d\n", totalsum);

    return 0;
}
