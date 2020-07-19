#include "libmx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int mx_count_amount_of_digits(long long int n);
int mx_count_string_size(char *str);
long long int mx_get_decrypt(long long int e, long long int el);
long long int mx_get_encrypt(long long int n);
int *mx_get_input_message(char* user_write);
int mx_get_num_by_index(char* str, int index);
int mx_get_prime_number(int min, int max);
long long int mx_modexp(long long int base, 
                        long long int e, 
                        long long int mod);

char *mx_rsa_decode(char *str);
char *mx_rsa_encrypt(char *str);
