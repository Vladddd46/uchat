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
#include "utils.h"

// Linked list with opened sockets.
typedef struct socket_list {
	int sock_fd;
	bool is_logged;
	char *login;
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
} chats_t;

// Chats messages context
typedef struct chat_message {
	int list_len;
	char *sender;
    char *time;
    char *message;
    struct chat_message *next; 
} chat_message_t;

// Server main functions.
int  get_port(char **argv);
int  listening_socket_init(int port);
void argv_validator(int argc);

// Database functions.
void    database_init();
sqlite3 *opening_db();

// Socket list.
int socket_list_add(connected_client_list_t    *head, int new_sock_fd);
int socket_list_free(connected_client_list_t   *head);
int socket_list_remove(connected_client_list_t *head, int sock_fd);
connected_client_list_t *socket_list_find(connected_client_list_t *head, int sock_fd);

// Logic
char *mx_database_communication(char *packet);
char *login_system(char *packet);
char *registration_system(char *packet);
chats_t *mx_get_users_chats(char *user);
char* mx_get_message(char* packet);
char* mx_add_message_by_id(char* packet);




