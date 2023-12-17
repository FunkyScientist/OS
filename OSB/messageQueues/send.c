#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <string.h>
#include <sys/msg.h>

#define SIZE 200 //max size of message that can be writed in message queue

struct mymsg
{
    int msg_type; 
    char msg_data[SIZE]; //store data in message queue
    
}message;


int main(int argc, char const *argv[])
{
    int running=1; //to keep while loop running
    //struct mymsg msg_data;
    
    char buffer[100]; //buffer -> memory block acting as temporary storage area

    int msg_id = msgget(153, 0666 | IPC_CREAT); //read/write permissions for user, group members and others
    
    if(msg_id == -1){
        printf("\nError creating message queue.");
    }

    while (running)
    {
                    
        printf("Enter text:\n");
        fgets(buffer, 100, stdin); //buffer to store data, 100 (how much data will be read), stdin({from where data will be read}takes input from keyboard in this case)
        
        message.msg_type = 1; //to assign msg_type value 1 because this will be used in receiver process
        strcpy(message.msg_data, buffer); //copy data from buffer in struct variable msg_data

        if(msgsnd(msg_id, (void*)&message, SIZE, 0 ) == -1){ //0: waiting for space to be available in the queue, 1:returns without sending the message.

            printf("\nMessage not sent.");

        }
        else
        {
            printf("\nMessage sent successfully.");
        }
        
    }
    return 0;
}