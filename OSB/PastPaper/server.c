#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <math.h>  // Include the math library for sqrt

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    float num;  // Modify the data type to float for receiving a number

    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2) {
         fprintf(stderr, "ERROR, no port provided\n");
         exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
         error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);  // Use htons for port number
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    while(1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");

        do {
            n = read(newsockfd, &num, sizeof(float));
            if (n < 0)
                error("ERROR reading from socket");

            if (num < 0)  // Check for invalid input
                error("ERROR: Invalid number");

            printf("I got : %f\n", num);

            // Calculate square root
            float result = sqrt(num);

            n = write(newsockfd, &result, sizeof(float));
            if (n < 0)
                error("ERROR writing to socket");

        } while (num >= 0);  // Modify the condition to end the loop

        close(newsockfd);
    }

    close(sockfd);
    return 0;
}
