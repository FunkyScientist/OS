#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{

    int id = fork();

    // Clone the calling process, creating an exact copy.
    // Return -1 for errors, 0 to the new process,
    // and the process ID of the new process to the old process

    if (id < 0)
    {
        printf("ERROR AAGYA");
    }
    if (id == 0)
    {
        printf("\nI AM THE CHILD : %d\n", id);
    }
    else
    {
        printf("\nI AM THE PARENT : %d\n", id);
    }

    return 0;
}
