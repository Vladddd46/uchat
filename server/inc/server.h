#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <netinet/in.h>
#include <sqlite3.h>
#include "libmx.h"
#include "cJSON.h"

#define CHILD 0

#define LOGIN_SUCCESS 			1
#define LOGIN_WRONG_LOGIN 		2
#define LOGIN_WRONG_PASSWORD 	3

void error(char *msg, int status);
void mx_client_process(int client_socket);
void database_init();
int login(int socket, char *packet);
sqlite3 *opening_db();
