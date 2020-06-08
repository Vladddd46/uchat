#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <netinet/in.h>
#include <math.h>

#define CHILD 0

void error(char *msg, int status);
void mx_client_process(int client_socket);
char *mx_strnew(int size);
char* mx_rsa_decode_password(char* str);
int mx_count_string_size(char* str);
int mx_get_num_by_index(char* str, int index);
int mx_count_amount_of_digits(long long int n);
long long int mx_modexp(long long int base, long long int e, long long int mod);
long long int mx_get_encrypt(long long int n);
long long int mx_get_decrypt(long long int e, long long int el);


