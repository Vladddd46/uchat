#include "crypt.h"

/* RSA algorythm - encode message into xx-yy-zz-zz-zz type
 * xx - first prime number (10 < x < 20)
 * yy - second prime number (15 < y < 40) 
 * (yy > xx)
 * zz - each number represend ecnrypted ASCII of char 
 */

static char *get_encrypt_1(int num1) {
    char *num1_str  = mx_itoa(num1);
    char *encrypt_1 = mx_strjoin(num1_str, "-");

    free(num1_str);
    return encrypt_1;
}

static char *get_encrypt_2(int num2, char *encrypt_1) {
    char *num2_str = mx_itoa(num2);
    char *encrypt_2 = mx_strjoin(encrypt_1, num2_str);

    free(num2_str);
    return encrypt_2;
}

static char *loop(char *str, int num1, int num2, char *encrypt_2) {
    int *input = mx_get_input_message(str);
    char *encrypt_3 = mx_strjoin(encrypt_2, "-");
    char *res  = mx_string_copy(encrypt_3);
    char *tmp;
    char *modexp_str;

    for(int i = 0; *(input + i) != -1; i++) {
        modexp_str = mx_itoa(mx_modexp(*(input + i), 
        mx_get_encrypt((num1 - 1) * (num2 - 1)), num1 * num2));
        tmp = mx_strjoin(res, modexp_str);
        free(res);
        res = tmp;
        tmp = mx_strjoin(res, "-");
        free(res);
        res = tmp;
        free(modexp_str);
    }
    *(res + mx_strlen(res) - 1) = '\0';
    free(input);
    free(encrypt_3);
    return res;
}

char *mx_rsa_encrypt(char *str) {
    unsigned long int num1 = mx_get_prime_number(10, 20);
    unsigned long int num2 = mx_get_prime_number(num1 + 1, 40);
    char *encrypt_1 = get_encrypt_1(num1);
    char *encrypt_2 = get_encrypt_2(num2, encrypt_1);
    char *res = loop(str, num1, num2, encrypt_2);

    free(encrypt_1);
    free(encrypt_2);
    return res;
}
