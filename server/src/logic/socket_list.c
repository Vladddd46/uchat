#include "socket_list.h"
#include <stdlib.h>

int socket_list_add (socket_list_t  * head, int new_sock_fd) {
    socket_list_t * p = NULL;
    socket_list_t * prev = NULL;
    if (head == NULL) return -1;
    for(p = head; p != NULL; prev = p , p = p->next) {
        if (p->sock_fd == new_sock_fd) return -3; // member exists
    }
    p = (socket_list_t *)malloc(sizeof(socket_list_t));
    if (p == NULL) return -1;
    p->sock_fd = new_sock_fd;
    p->is_logged = false;
    p->next = NULL;
    prev->next = p;
    return 0;
}

socket_list_t * socket_list_find (socket_list_t  * head, int sock_fd) {
    if (head == NULL) return NULL;
    for(socket_list_t * p = head; p != NULL; p = p->next) {
        if (p->sock_fd == sock_fd) {
        	return p;
        }
    }
    return NULL;
}

int socket_list_remove (socket_list_t * head, int sock_fd) {
    if (head == NULL) return -1;
    for(socket_list_t * p = head; p != NULL; p = p->next) {
        if (p->next != NULL && (p->next)->sock_fd == sock_fd) {
            socket_list_t * del = p->next;
            p->next = del->next;
            free(del);
            return 0;
        }
    }
    return -2; // not found
}

int socket_list_free(socket_list_t * head) {
	if (head == NULL) return -1;
	socket_list_t * del = NULL;
    while (head->next != NULL) {
    	del = head->next;
    	head->next = del->next;
    	free(del);
    }
    return 0;
}
