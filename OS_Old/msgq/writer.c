#include "header.h"

int main(int argc, char const *argv[])
{

    if (argc != 2)
    {
        printf("\nUsage : %s <Msg Type>\n\n", argv[0]);
        return 0;
    }

    int qid;

    my_msg msg;

    if ((qid = msgget(KEY, PERM | IPC_CREAT)) == -1)
    {
        perr();
    }

    long mtype = atol(argv[1]);

    while (1)
    {
        printf("\nEnter SUMN : ");
        fgets(msg.text, SIZE, stdin);
        msg.type = mtype;

        if ((msgsnd(qid, (my_msg *)&msg, SIZE, 0)) == -1)
        {
            perr();
        }

        if ((strncmp(msg.text, "-1", 2)) == 0)
        {
            break;
        }
    }

    return 0;
}
