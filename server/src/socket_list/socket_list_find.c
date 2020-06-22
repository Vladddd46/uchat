#include "server.h"

// Returns socket node by given socket id.
socket_list_t *socket_list_find(socket_list_t *head, int sock_fd) {
    if (head == NULL) return NULL;
    for(socket_list_t *p = head; p != NULL; p = p->next) {
        if (p->sock_fd == sock_fd)
            return p;
    }
    return NULL;
}
