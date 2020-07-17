#include "crypt.h"

// Main encrypt and descrypt alorithm.
long long int mx_modexp(long long int base, 
                        long long int e, 
                        long long int mod) {
    unsigned long long res = 1;

    while (e != 0) {
        if ((e & 1) != 0) {
            res = (1ll * res * base) % mod;
        }
        base = (1ll * base * base) % mod;
        e >>= 1;
    }
    return res;
}
