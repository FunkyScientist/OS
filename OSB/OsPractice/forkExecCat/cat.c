#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    
        int inFile = open("Input.txt", O_RDONLY);
        dup2(inFile, STDIN_FILENO); //takes input from inFile instead of taking input from keyboard
       // dup2(fd[1], STDOUT_FILENO);
        execl("/usr/bin/cat", "cat", NULL); //concatenate files and print on the standard output
    return 0;
}
