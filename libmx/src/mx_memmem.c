#include "libmx.h"

/*
 * The memmem() function locates the first occurrence 
 * of the byte string little in the byte string big.
 */
void *mx_memmem(void *big, size_t big_len, void *little, size_t little_len) {
    unsigned long blen = (unsigned long)big_len;
    unsigned long llen = (unsigned long)little_len;
    char *b = (char *)big;
    char *l = (char *)little;

    if (blen < llen || llen == 0 || blen == 0)
        return NULL;

    // Walking through each char in big.
    unsigned long i = 0;
    while(i < blen){
        // Identity of first symbols are found
        if (b[i] == l[0]){
            // Further check of identity.
            unsigned long j = 0;
            unsigned long tmp = i;
            while (b[tmp] == l[j]){
                // Little in big is found.
                if (j == llen - 1)
                    return &b[i];
                j++;
                tmp++;
            }
        }
        i++;
    }
    return NULL;
}
