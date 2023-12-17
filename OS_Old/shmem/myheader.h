#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define BUFSIZE 3

#define PERM (S_IRUSR | S_IWUSR | IPC_CREAT)

typedef struct
{
	int SID;
	char name[10];
} student;
