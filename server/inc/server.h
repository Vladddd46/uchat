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
#include <stdbool.h>
#include "libmx.h"
#include "cJSON.h"
#include "socket_list.h"
#include <sys/types.h>
#include <sys/stat.h>

#define CHILD 0

// Linked list with opened sockets.
typedef struct socket_list {
	int sock_fd;
	bool is_logged;
	struct socket_list *next;
} connected_client_list_t;

// Server context.
typedef struct {
	fd_set read_descriptors;
	connected_client_list_t head;
} server_context_t;

// Chats context
typedef struct chats {
    char* chat_name;
    char* last_message;
    struct chats *next;
    // chats(): next(NULL) {}
} chats_t;

// Chats messages context
typedef struct chat_message {
	char* sender;
    char* time;
    char* message;
    struct chat_message *next;
} chat_message_t;

// Server main functions.
int  get_port(char **argv);
int  listening_socket_init(int port);
void argv_validator(int argc);
void error(char *msg, int status);

void mx_deamon_start(void);

// Sending email function


char *login_determiner(char *send_packet);
// Database functions.
void    database_init();
sqlite3 *opening_db();

// Socket list.
int socket_list_add(connected_client_list_t    *head, int new_sock_fd);
int socket_list_free(connected_client_list_t   *head);
int socket_list_remove(connected_client_list_t *head, int sock_fd);
connected_client_list_t *socket_list_find(connected_client_list_t *head, int sock_fd);

// Json
char *get_value_by_key(char *json_str, char *key);
char *json_packet_former(int num, ...);

// Logic
char *mx_database_communication(char *packet);
char *login_system(char *packet);
char *registration_system(char *packet);

// help funcs
char *packet_len_prefix_adder(char *packet);
