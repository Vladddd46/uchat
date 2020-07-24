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
    char* chat_id;
    struct chats *next;
} chats_t;

// Chats messages context
typedef struct chat_message {
	int list_len;
	char *sender;
    char *time;
    char *message;
    char *msg_type;
    struct chat_message *next; 
} chat_message_t;

typedef struct users_list {
	int  id;
	char *nickname;
	char *login;
	struct users_list *next;
} users_list_t;

// Server main functions.
int  get_port(char **argv);
int  listening_socket_init(int port);
void argv_validator(int argc);
void mx_login_user_socket(connected_client_list_t *p, char *send_packet, char **receivers);
int  mx_user_is_already_logged_in(connected_client_list_t *list, char *user_login);

// Database functions.
void    database_init();
sqlite3 *opening_db();
void def_database();
void dberror(sqlite3 *db, int status, char *msg);
void db_msg_error(int status, char *msg_error);
char *mx_get_nickname_by_login(char *login);

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
char* mx_chat_render(char* packet);
char* mx_add_message_by_id(char* packet);
char* mx_find_user(char* packet);
char* mx_add_contact(char* packet);
char* mx_change_password(char* pakcet);

// additional 
void mx_push_back_message_node(chat_message_t **list, char *sender, 
							   char *time, char *message, char *msg_type);
int mx_chats_list_len(chats_t *chat);
int mx_get_last_message_id(int chat_id);
void mx_null_value_error(char *func_name);




