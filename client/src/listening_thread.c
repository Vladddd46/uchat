#include "client.h"

/*
 * Callback function, which
 * listening for incoming packets from server.
 */

void *listening_thread(void *arg) {
    int  *socket = (int *)arg;
    char buffer[255];
    bzero(&buffer, 255);

    while(1) {
        read(*socket, buffer, 254);
        printf("listening_thread = %s\n", buffer);
        // refreshing buffer.
        bzero(&buffer, 255);
    }
    return NULL;
}