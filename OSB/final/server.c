//Name:Abdul Rehman Khalid
//Reg #:SP21-BSE-038

#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void error(const char *msg);

int main(int argc, char *input_data[]) {
    int abba_socket, bacha_socket, port_ka_number;
    int bucha;
    char c;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    int n;

    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    abba_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (abba_socket < 0)
        error("ERROR opening socket");

    bzero((char*) &serv_addr, sizeof(serv_addr));
    port_ka_number = atoi(input_data[1]);
    serv_addr.sin_family = AF_INET;
    
    
    
    
    
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port_ka_number);

    if (bind(abba_socket, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERRR on binding");

    listen(abba_socket, 5);
    clilen = sizeof(cli_addr);

    while (1) {
        bacha_socket = accept(abba_socket, (struct sockaddr*) &cli_addr, &clilen);

        if (bacha_socket < 0)
            error("ERROR on accept");

        bucha = fork();

        if (bucha < 0)
            error("ERROR in new process creation");

        if (bucha == 0) {   // child process
            close(abba_socket);
            bzero((char*) &c, sizeof(c));
            n = read(bacha_socket, &c, 1);

            if (n < 0)
                error("ERROR reading from socket");

            printf("I got %c from client\n", c);
            n = write(bacha_socket, &c, 1);

            if (n < 0)
                error("ERROR writing to socket");

            exit(0);
        }
        else
            close(bacha_socket);
    }

    close(abba_socket);
    return 0;
}

void error(const char *msg) {
    perror(msg);
    exit(1);
}

