#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd;    // File descriptor for the server socket.
    int newsockfd; // File descriptor for the newly created socket after accepting a connection.
    int portno;    // Port number for the server to bind and listen on.
    char c;        // Used to store a character received from the client.

    socklen_t clilen;             // Length of the client address structure.
    struct sockaddr_in serv_addr; // Structure to hold server address information.
    struct sockaddr_in cli_addr;  // Structure to hold client address information.

    int n; // Used to store the return value of certain functions, such as the number of characters read or written.

    // Check if the command-line argument for the port number is provided.
    if (argc < 2)
    {
        // Print an error message to standard error.
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    // Create a socket with AF_INET (IPv4), SOCK_STREAM (TCP), and protocol 0.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Check if the socket creation was successful.
    if (sockfd < 0)
        error("ERROR opening socket");

    bzero((char *)&serv_addr, sizeof(serv_addr)); // Set all the bytes of the serv_addr structure to zero.

    portno = atoi(argv[1]); // Convert the port number from string to integer.

    serv_addr.sin_family = AF_INET; // Set the address family of the serv_addr structure to AF_INET (IPv4).

    // Set the IP address to INADDR_ANY, allowing the server to accept connections on any available network interface.
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    serv_addr.sin_port = portno; // Set the port number in network byte order.

    // Attempt to bind the socket to the specified address and port.
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    // Start listening for incoming connections on the bound socket.
    listen(sockfd, 5);

    // Set the length of the client address structure.
    clilen = sizeof(cli_addr);

    while (1)
    {
        // Accept a connection on the listening socket (sockfd).
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

        // Check if the accept operation was successful.
        if (newsockfd < 0)
            error("ERROR on accept");

        // Loop to continuously read and write data with the connected client until 'Q' is received.
        do
        {
            // Read a character from the connected client.
            n = read(newsockfd, &c, 1);
            if (n < 0)
                error("ERROR reading from socket");

            // Print the received character to the console.
            printf("I got : %c\n", c);

            // Increment the received character.
            ++c;

            // Write the incremented character back to the connected client.
            n = write(newsockfd, &c, 1);
            if (n < 0)
                // If an error occurs during writing, call the error function.
                error("ERROR writing to socket");
        } while (--c != 'Q'); // Continue the loop until 'Q' is received.

        // Close the socket for the connected client.
        close(newsockfd);
    }
}