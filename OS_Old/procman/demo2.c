#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int id = fork();
    int n;
    if (id == 0)
    {
        n = 1;
    }
    else
    {
        n = 6;
    }

    wait();

    for (int i = n; i < n + 5; i++)
    {
        printf("%d ", i);
        fflush(stdout);
    }
    return 0;
}
