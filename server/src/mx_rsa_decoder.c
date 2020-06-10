#include "uchat.h"

/* Decrypt ecnrypted string from type xx-yy-zz-zz-zz to string type abc...
                  xx - first prime number (10 < x < 20)
                  yy - second prime number (15 < y < 40) 
                    (yy > xx)
                  zz - each number represend ecnrypted ASCII of char */

char* mx_rsa_decode_password(char* str) {
    unsigned long int num1 = mx_get_num_by_index(str, 0);
    unsigned long int num2 = mx_get_num_by_index(str, 1);

    long long int el = (num1 - 1) * (num2 - 1);
    long long int multiplyNums = num1 * num2;
    char* descrypt = mx_strnew(100);

    long long int e = mx_get_encrypt(el);
    long long int d = mx_get_decrypt(e, el);

    for(int i = 0; i < mx_count_string_size(str); i++) {
        *(descrypt + i) = mx_modexp(mx_get_num_by_index(str, i + 2), d, multiplyNums);
    }

    return descrypt;
}
