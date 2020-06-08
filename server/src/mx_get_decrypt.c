#include "uchat.h"

/* Calculate key for decrypting message */

long long int mx_get_decrypt(long long int e, long long int el) {
    long long int r = 1;

    do {
        r += el;
    } while (r % e != 0);

    return r / e;;
}
