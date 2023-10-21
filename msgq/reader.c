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
        msg.type = mtype;

        if ((msgrcv(qid, (my_msg *)&msg, SIZE, mtype, 0)) == -1)
        {
            perr();
        }

        printf("\nRECEIVED : %s\n", msg.text);

        if ((strncmp(msg.text, "-1", 2)) == 0)
        {
            break;
        }
    }

    msgctl(qid, IPC_RMID, 0);

    return 0;
}
