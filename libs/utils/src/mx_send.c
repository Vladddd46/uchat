#include "utils.h"

/*
 * Takes socket and the packet as parameters.
 * Does the encryption of the packet.
 * Adds 8-byte prefix(represents lengths pf packet) to the encrypted
 * packet.
 * sends packet on socket.
 */
void mx_send(int socket, char *packet) {
    char *prefixed_packet  = packet_len_prefix_adder(packet);

    send(socket, prefixed_packet, (int)strlen(prefixed_packet), 0);
    free(prefixed_packet);
 }