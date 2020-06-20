#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <netinet/in.h>
#include <sqlite3.h>
#include <pthread.h>
#include "libmx.h"
#include "cJSON.h"
#include "socket_list.h"
#include <sys/types.h>
#include <sys/stat.h>

#define CHILD 0

#define LOGIN_SUCCESS 			1
#define LOGIN_FAIL  	     	2

typedef struct {
	fd_set read_descriptors;
	socket_list_t head;
} server_context_t;

void error(char *msg, int status);
void *handle_client(void *client_socket);
void database_init();
int login(int socket, char *packet);
sqlite3 *opening_db();

int listening_socket_init(int port);

char *json_packet_former(int num, ...);

void mx_deamon_start();
