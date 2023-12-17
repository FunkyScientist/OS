#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[]){

    int loc = open ("Yoyo.txt", O_RDWR | O_CREAT);

    if(loc == -1){
        printf("Error.");
    }

    dup2(loc, STDOUT_FILENO);
    close(loc);

    execl("/usr/bin/grep", "grep", "l", NULL);
    //execl("/usr/bin/curl", "curl", "ipinfo.io", NULL);

    return 0;
}