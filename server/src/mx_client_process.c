#include "uchat.h"

void mx_client_process(int client_socket) {
    int n;
    char buffer[256];
    bzero(buffer,256);
    n = read(client_socket,buffer,255);
    // printf("%s\n", mx_rsa_decode_password("13-17-72-104-173-54"));
    printf("%d | %s\n", n, buffer);
    printf("%d | %s\n", n, mx_rsa_decode_password(buffer));
}
