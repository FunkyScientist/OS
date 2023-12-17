#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


// Description: Prints an error message using perror and exits the program.
//   - msg: A pointer to a string containing the error message to be displayed.
void error(const char *msg)
{
    // perror prints the error message followed by a description of the last error that occurred.
    perror(msg);

    // exit(0) terminates the program with a status code of 0, indicating a successful termination.
    exit(0);
}

// use ss dst 127.0.0.1 -p  to view connections

int main(int argc, char *argv[])
{
    char c;

    int sockfd;       // File descriptor for the socket.
    int portno;       // Port number for the connection.
    int n;            // Used to store the return value of certain functions, such as the number of characters read or written.
    int term_con = 0; // Flag indicating whether the program should terminate the connection (initially set to 0).

    struct sockaddr_in serv_addr; // Structure to hold server address information.

    struct hostent *server; // Structure to hold information about the host (server).

    // Check if the command-line arguments are provided correctly.
    if (argc < 3)
    {
        // Print usage information to standard error.
        fprintf(stderr, "usage %s hostname port\n", argv[0]);

        // Exit the program with a status code of 0.
        exit(0);
    }

    portno = atoi(argv[2]); // Convert the port number from string to integer.

    // Create a socket with AF_INET (IPv4), SOCK_STREAM (TCP), and protocol 0.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        error("ERROR opening socket"); // Call the error function if opening the socket fails.

    server = gethostbyname(argv[1]); // Get host information using the provided hostname.

    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    bzero((char *)&serv_addr, sizeof(serv_addr)); // Set all the bytes of the serv_addr structure to zero.

    serv_addr.sin_family = AF_INET; // Set the address family of the serv_addr structure to AF_INET (IPv4).

    // Copy the server's address from server->h_addr to serv_addr.sin_addr.s_addr.
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);

    // Set the port number in network byte order.
    serv_addr.sin_port = portno;
    // printf("h_addr: %s\n", inet_ntoa(serv_addr.sin_addr));

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) // Attempt to establish a connection to the server using the created socket.
        error("ERROR connecting");

    while (1)
{
    printf("Please enter a single char: ");

    // Read a character from standard input.
    c = (char)getc(stdin);

    // Flush the input buffer to remove the newline character.
    //fflush(stdin);

    // Write the read character to the socket.
    n = write(sockfd, &c, 1);
    if (n < 0)
        // If an error occurs during writing, call the error function.
        error("ERROR writing to socket");

    // If the character is 'Q', close the socket and return from the program.
    if (c == 'Q')
    {
        close(sockfd);
        return 0;
    }

    // Read a character from the socket.
    n = read(sockfd, &c, 1);
    if (n < 0)
        // If an error occurs during reading, call the error function.
        error("ERROR reading from socket");

    // Print the received character from the server.
    printf("I got %c from the server\n", c);
}

}