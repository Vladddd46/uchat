#ifndef SOCKET_LIST_H
#define SOCKET_LIST_H
#include <stdbool.h>

typedef struct socket_list {
	int sock_fd;
	bool is_logged;
	struct socket_list *next;
} socket_list_t;

int socket_list_add (socket_list_t  * head, int new_sock_fd);
socket_list_t * socket_list_find (socket_list_t  * head, int sock_fd);
int socket_list_remove (socket_list_t * head, int sock_fd);
int socket_list_free(socket_list_t * head);

#endif
