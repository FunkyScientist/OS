#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/shm.h>

#define KEY 69
#define PERM (S_IRUSR | S_IWUSR)
#define SIZE 100