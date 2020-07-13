#include "client.h"

/*
 * Create structure, where client address is described.
 * 1. server`s address
 * 2. ip version AF_INET = IPv4
 * 3. server`s port.
 */
struct sockaddr_in mx_client_address_describer(int port) {
    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Local Host
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);

    return client_addr;
}

