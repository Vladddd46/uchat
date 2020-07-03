#include "utils.h"

/*
 * Adds 8 bytes to the packet.
 * This 8 bytes represent lenth of packet.
 * if len. is less than 8 bytes long -> empty bytes with '*' are filled.
 */
char *packet_len_prefix_adder(char *packet) {
    int len      = (int)strlen(packet);
    char *slen   = mx_itoa(len);
    char *prefix = mx_strnew(8);
    char *result;

    for (int i = 0; i < 8; ++i)
        prefix[i] = '*';
    for (int i = 0; slen[i]; ++i)
        prefix[i] = slen[i];

    result = mx_strjoin(prefix, packet);
    free(slen);
    free(prefix);
    return result;
}
