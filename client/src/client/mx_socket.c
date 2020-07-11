#include "client.h"

// Create socket TCP and IPv4
int mx_socket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    error("Error while creating socket", sockfd);

    return sockfd;
}

