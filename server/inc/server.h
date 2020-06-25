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

#define CHILD 0

#define LOGIN_SUCCESS 			1
#define LOGIN_FAIL  	     	2

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
    struct chats_t* next;
    // chats(): next(NULL) {}
} chats_t;



// Server main functions.
int  get_port(char **argv);
int  listening_socket_init(int port);
void argv_validator(int argc);
void error(char *msg, int status);

// Database functions.
void    database_init();
char    *mx_database_communication(char *packet);
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
char *login_system(char *packet);
char *registration_system(char *packet);
chats_t* mx_get_users_chats(char* user);
// int mx_add_message(const char *str, char* user, char* sender, char* time, char* message);
chats_t* mx_get_users_chats(char* user);

