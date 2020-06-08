#include "uchat.h"

/* Check if numbers are true for RSA formula (see full Evklid algorythm: ed = 1 (mod p(n))) */

static long int bcd(long long int n1, long long int n2){
    while(n1 > 0) {
        long int temp;

        temp = n1;
        n1 = n2 % n1;
        n2 = temp;
    }

    return n2;
}

/* Calculate ecnrypting key */

long long int mx_get_encrypt(long long int n) {
    long long int e;

    for (e = 2; e < n; e++)
        if(bcd(e, n) == 1)
            return e;

    return -1;
}
