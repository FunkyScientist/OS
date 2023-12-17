#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <math.h> // Include the math library for sqrt

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    char c;
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    float number; // Modify the data type to float for sending a number

    if (argc < 3)
    {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    do
    {
        printf("Please enter a positive number (negative to quit): ");
        scanf("%f", &number);

        n = write(sockfd, &number, sizeof(float));
        if (n < 0)
            error("ERROR writing to socket");

        if (number < 0)
            break;

        n = read(sockfd, &number, sizeof(float));
        if (n < 0)
            error("ERROR reading from socket");

        printf("Result is %f\n", number);

    } while (number >= 0);

    close(sockfd);
    return 0;
}
