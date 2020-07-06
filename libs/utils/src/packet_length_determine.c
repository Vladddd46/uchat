#include "utils.h"

// Read first 8 bytes from packet. (They represent the length of the packet.)
int packet_length_determine(int socket) {
    char buf[8];
    bzero(buf, 8);
    recv(socket, buf, 8, 0);
    int packet_len = atoi(buf);

    return packet_len;
}
