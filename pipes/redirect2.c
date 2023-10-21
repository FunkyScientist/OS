#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{

    int err = open("ip.txt", O_RDWR | O_CREAT);
    if (err == -1)
    {
        printf("ERROR AAVAY\n");
        return 1;
    }

    dup2(err, STDOUT_FILENO);
    close(err);

    // char p[] = {"Hello"};
    // write(1, &p, sizeof(p));

    execl("/usr/bin/curl", "curl", "ipinfo.io", NULL);

    return 0;
}
