#include "libmx.h"

/*
 * The memset() function writes len bytes of value c 
 * (converted to an unsigned char) to the string b.
 */
void *mx_memset(void *b, int c, size_t len) {
    unsigned int n1 = len;
    char *string = b;

    for(unsigned int i = 0; i < n1; i++)
        string[i] = c;
    return string;
}
