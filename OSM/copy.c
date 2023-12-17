#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MANNAME 80
#define R_FLAGS O_RDONLY
#define W_FLAGS (O_WRONLY | O_CREAT)
#define W_PERMS (S_IRUSR | S_IWUSR)
#define BLKSIZE 512

int copyfile(int fromfd, int tofd);
void *copyfilepass(void *arg);

typedef struct {
    int args[2];
    pthread_t tid;
} copy_t;

int main(int argc, char *argv[]) {
    int *bystep;
    copy_t *copies;
    int error;
    char filename[MANNAME];
    int i;
    int numcopiers;
    int totalbytes = 0;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s infile outfile copies\n", argv[0]);
        return 1;
    }

    numcopiers = atoi(argv[3]);
    if ((copies = (copy_t *)calloc(numcopiers, sizeof(copy_t))) == NULL) {
        perror("Failed to allocate copier space");
        return 1;
    }

    for (i = 0; i < numcopiers; i++) {
        copies[i].tid = pthread_self();

        if (snprintf(filename, MANNAME, "%s.%d", argv[1], i + 1) >= MANNAME) {
            fprintf(stderr, "Input filename %s.%d too long\n", argv[1], i + 1);
            continue;
        }

        if ((copies[i].args[0] = open(filename, R_FLAGS)) == -1) {
            fprintf(stderr, "Failed to open source file %s: %s\n", filename, strerror(errno));
            continue;
        }

        if (snprintf(filename, MANNAME, "%s.%d", argv[2], i + 1) >= MANNAME) {
            fprintf(stderr, "Output filename %s.%d too long\n", argv[2], i + 1);
            continue;
        }

        if ((copies[i].args[1] = open(filename, W_FLAGS, W_PERMS)) == -1) {
            fprintf(stderr, "Failed to open destination file %s: %s\n", filename, strerror(errno));
            close(copies[i].args[0]); // Close the source file
            continue;
        }

        if ((error = pthread_create(&(copies[i].tid), NULL, copyfilepass, (void *)copies[i].args)) != 0) {
            fprintf(stderr, "Failed to create thread %d: %s \n", i + 1, strerror(error));
            copies[i].tid = pthread_self(); // Cannot be the value for a new thread
        }
    }

    for (i = 0; i < numcopiers; i++) {
        if (pthread_equal(copies[i].tid, pthread_self())) // Not created
            continue;

        if ((error = pthread_join(copies[i].tid, (void **)&bystep)) != 0) {
            fprintf(stderr, "Failed to join thread %d: %s\n", i + 1, strerror(error));
            continue;
        }

        if (bystep == NULL) {
            fprintf(stderr, "Thread %d failed to return status\n", i + 1);
            continue;
        }

        printf("Thread %d copied %d bytes from %s.%d to %s.%d\n", i, *bystep, argv[1], i + 1, argv[2], i + 1);
        totalbytes += *bystep;
    }

    printf("Total Bytes Copied = %d\n", totalbytes);

    free(copies);
    return 0;
}

void *copyfilepass(void *arg) {
    int *argint = (int *)arg;
    argint[2] = copyfile(argint[0], argint[1]);
    close(argint[0]);
    close(argint[1]);
    return argint + 2;
}

int copyfile(int fromfd, int tofd) {
    char buf[BLKSIZE];
    int bytesread, byteswritten, totalbytes = 0;

    while ((bytesread = read(fromfd, buf, BLKSIZE)) > 0) {
        if ((byteswritten = write(tofd, buf, bytesread)) != bytesread) {
            perror("Error writing to destination file");
            return -1;
        }
        totalbytes += byteswritten;
    }

    if (bytesread < 0) {
        perror("Error reading from source file");
        return -1;
    }

    return totalbytes;
}
