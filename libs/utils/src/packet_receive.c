#include "utils.h" 

/*
 * Determines length of incomming packet.
 * Receives encrypted packet.
 * Decrypts packet.
 * Returns pacekt.
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
    int  packet_len        = packet_length_determine(socket);
    char *encrypted_packet = mx_strnew(packet_len);
    char *decrypted_packet;
    int  index = 0;

    while(index < packet_len) {
        recv(socket, &encrypted_packet[index], 1, 0);
        index++;
    }
    decrypted_packet = mx_rsa_decrypt(encrypted_packet);
    free(encrypted_packet);
    return decrypted_packet;
}
