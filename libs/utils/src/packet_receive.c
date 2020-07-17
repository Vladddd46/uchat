#include "utils.h" 

/*
 * Receives crypted packet from socket.
 * Decrypts packet and returns it.
 */

// Read first 8 bytes from packet. (They represent the length of the packet.)
static int packet_length_determine(int socket) {
    char buf[8];
    bzero(buf, 8);
    recv(socket, buf, 8, 0);
    int packet_len = atoi(buf);

    return packet_len;
}

// Receiving packet from the socket.
char *packet_receive(int socket) {
    int  packet_len = packet_length_determine(socket);
    int  index      = 0;
    char *packet    = mx_strnew(packet_len);
    char *encrypted_packet;

    while(index < packet_len) {
        recv(socket, &packet[index], 1, 0);
        index++;
    }

    // encrypted_packet = mx_rsa_decode(packet);
    // free(packet);
    // return encrypted_packet;
    return packet;
}

