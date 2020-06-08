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


