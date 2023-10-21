#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    printf("\nAIK DAFA CHALU GA\n");

    int yoyo = fork();

    // Clone the calling process, creating an exact copy.
    // Return -1 for errors, 0 to the new process,
    // and the process ID of the new process to the old process.

    if (yoyo < 0)
    {
        printf("\n\nERROR AAGYA BE\n\n");
    }

    int wt = wait(NULL);

    if (yoyo == 0)
    {

        printf("MAI CHILD HU. MERE CHILD KI YOYO YEH HAI : %d\n", yoyo);
        printf("PID : %d\t PPID : %d\n", getpid(), getppid());
    }
    else
    {
        printf("MAI PARENT HU. MERI YOYO YEH HAI : %d\n", yoyo);
        printf("PID : %d\t PPID : %d\n", getpid(), getppid());
    }

    return 0;
}
