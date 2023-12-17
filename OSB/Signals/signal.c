#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void my_sig_handler(int signo)
{
    printf("caling from signal handler\n");
}

int main(void)
{
    // Define a structure for handling signals
    struct sigaction act;

    // Initialize counters for the nested loops
    int count, count2;
    count = count2 = 0;

    // Initialize a variable to store the sum of sin(x) values
    double sum = 0;

    // Declare a variable to store a random number
    double x;

    // Nested loops for performing a computation (sin(x)) a large number of times
    for (; count < 100000000; ++count)
        for (; count2 < 100000000; ++count2)
        {
            // Generate a random number between 0 and 1 and calculate x
            x = ((rand() + 0.5) / RAND_MAX + 1.0);

            // Accumulate the sine values in the 'sum' variable
            sum += sin(x);
        }

    // Configure a signal handler using the sigaction structure
    act.sa_handler = my_sig_handler;

    // Set flags for the sigaction structure (no special flags in this case)
    act.sa_flags = 0;

    // Check if setting the signal handler for SIGINT is successful
    if ((sigaction(SIGINT, &act, NULL) == -1))
    {
        // Print an error message if setting the signal handler fails
        perror("failed to set sigint handler\n");
        return 1;
    }

    // Reset the sum variable
    sum = 0;

    // Print a message indicating that the signal handler has been installed for SIGINT
    printf("signal handler installed for sigint\n");

    // Reset counters for the nested loops
    count = count2 = 0;

    // Nested loops for performing a computation (sin(x)) a large number of times after installing the signal handler
    for (; count < 100000000; ++count)
        for (; count2 < 100000000; ++count2)
        {
            // Generate a random number between 0 and 1 and calculate x
            x = ((rand() + 0.5) / RAND_MAX + 1.0);

            // Accumulate the sine values in the 'sum' variable
            sum += sin(x);
        }

    // Declare a signal set
    sigset_t signal_set;

    // Initialize the signal set to be empty
    sigemptyset(&signal_set);

    // Add SIGSEGV (Segmentation Fault) to the signal set
    sigaddset(&signal_set, SIGSEGV);

    // Block the SIGSEGV signal using sigprocmask
    sigprocmask(SIG_BLOCK, &signal_set, NULL);

    // Print a message indicating that SIGSEGV is blocked
    printf("sigsegv blocked\n");

    // Reset counters for the nested loops
    count = count2 = 0;

    // Trigger a segmentation fault using the kill function
    kill(0, SIGSEGV);

    // Nested loops for performing a computation (sin(x)) a large number of times after triggering the segmentation fault
    for (; count < 100000000; ++count)
        for (; count2 < 100000000; ++count2)
        {
            // Generate a random number between 0 and 1 and calculate x
            x = ((rand() + 0.5) / RAND_MAX + 1.0);

            // Accumulate the sine values in the 'sum' variable
            sum += sin(x);
        }

    // Print a message indicating that the program is going to unblock SIGSEGV
    printf("going to unblock sigsegv\n");

    // Unblock the SIGSEGV signal using sigprocmask
    sigprocmask(SIG_UNBLOCK, &signal_set, NULL);

    // Print a message indicating that SIGSEGV is unblocked
    printf("sigsegv unblocked\n");

    // Return 0 to indicate successful execution
    return 0;
}
