#include "server.h"

/*
 * Adds new node with socket (connection)
 * description in linked list.
 */
int socket_list_add(socket_list_t *head, int new_sock_fd) {
    socket_list_t *p    = NULL;
    socket_list_t *prev = NULL;
    if (head == NULL) return -1;

    for(p = head; p != NULL; prev = p , p = p->next) {
        if (p->sock_fd == new_sock_fd) 
            return -3; // member exists
    }
    p = (socket_list_t *)malloc(sizeof(socket_list_t));
    if (p == NULL) return -1;
    p->sock_fd = new_sock_fd;
    p->is_logged = false;
    p->next = NULL;
    prev->next = p;
    return 0;
}
