#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>

#define PERM (S_IRUSR | S_IWUSR)

// #define PERM (0600)
// S_IRUSR (READ PERMISSION TO USER ) = 0400
// S_IRUSR (WRITE PERMISSION TO USER ) = 0200

#define KEY 69
#define SIZE 100

typedef struct
{
    long type;
    char text[SIZE];
} my_msg;

void perr()
{
    printf("\nERROR hehe\n");
}