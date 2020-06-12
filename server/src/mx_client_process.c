#include "server.h"

void mx_client_process(int client_socket) {
    int n;
    char buffer[256];
    bzero(buffer,256);
    while(1) {
        n = read(client_socket, buffer, 255);
       

        printf("%s\n", buffer);
        // refreshing buffer.
        bzero(buffer,256);
    }
}
