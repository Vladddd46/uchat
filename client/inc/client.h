#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>
#include <time.h>

#define CHILD 0

void error(char *msg, int status);
int mx_strlen(char *s);
char *mx_strnew(int size);
char *mx_itoa(int number);
char *mx_strjoin(char *s1, char *s2);


/* Client encoder part */

int* mx_get_input_message(char* user_write);
int mx_get_prime_number(int min, int max);
int mx_count_amount_of_digits(long long int n);
char* rsa_decode_password(char* str);
long long int mx_modexp(long long int base, long long int e, long long int mod);
long long int mx_get_decrypt(long long int e, long long int el);
long long int mx_get_encrypt(long long int n);



