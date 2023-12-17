//Name:Abdul Rehman Khalid
//Reg #:SP21-BSE-038

#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void error(const char *msg);

int main(int argc, char *input_data[]) {
    int mysocket, alpha, n;
    char c;
    struct hostent *server;
    struct sockaddr_in serv_addr;

    if (argc < 3) {
        fprintf(stderr, "ERROR, usage: %s hostname port\n", input_data[0]);
        exit(1);
    }

    mysocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mysocket < 0)
        error("ERROR opening socket");

    server = gethostbyname(input_data[1]);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    alpha = atoi(input_data[2]);

    bcopy((char*) server->h_addr, (char*) &serv_addr.sin_addr.s_addr, server->h_length);
    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(alpha);

    if (connect(mysocket, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    while (1) {
        printf("Please enter a single char:");
        c = getchar();

        if (c == 'Q') {
            close(mysocket);
            exit(0);
        }

        n = write(mysocket, &c, 1);
        if (n < 0)
            error("ERROR writing to socket");

        n = read(mysocket, &c, 1);
        if (n < 0)
            error("ERROR reading from socket");

        printf("I got %c from server\n", c);
    }

    close(mysocket);
    return 0;
}

void error(const char *msg) {
    perror(msg);
    exit(1);
}

