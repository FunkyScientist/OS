#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/msg.h>

struct mymsg
{
    int msg_type;
    char msg_data[BUFSIZ];
} message;

int main(int argc, char const *argv[])
{
    int running = 1;
    int order = 0; // messages will be retreived in the same order in which they were written in the queue

    int msg_id = msgget(153, 0666 | IPC_CREAT);

    if (msg_id == -1)
    {
        return 1;
    }

    while (running)
    {
        msgrcv(msg_id, (void *)&message, BUFSIZ, order, 0);
        printf("\nData received: %s", message.msg_data);

    }
     msgctl(msg_id, IPC_RMID, 0);

    return 0;
}
