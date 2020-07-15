#include "crypt.h"

/* RSA algotyrm - encode message into xx-yy-zz-zz-zz type
 * xx - first prime number (10 < x < 20)
 * yy - second prime number (15 < y < 40) 
 * (yy > xx)
 * zz - each number represend ecnrypted ASCII of char 
 */
char *mx_rsa_encrypt(char *str) {
    int *input = mx_get_input_message(str);
    unsigned long int num1 = mx_get_prime_number(10, 20);
    unsigned long int num2 = mx_get_prime_number(num1 + 1, 40);
    char *encrypt = mx_strjoin(mx_itoa(num1), "-");

    // add xx-prime number to srting and yy-prime number next to it
    encrypt = mx_strjoin(encrypt, mx_itoa(num2));
    encrypt = mx_strjoin(encrypt, "-");
    
    // Encrypt each character and put it to encrypt string
    for(int i = 0; *(input + i) != -1; i++) {
        encrypt = mx_strjoin(encrypt, mx_itoa(mx_modexp(*(input + i), 
        mx_get_encrypt((num1 - 1) * (num2 - 1)), num1 * num2)));
        encrypt = mx_strjoin(encrypt, "-");
    }
    *(encrypt + mx_strlen(encrypt) - 1) = '\0';
    return encrypt;
}
