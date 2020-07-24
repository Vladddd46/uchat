#include "server.h"

// Returns socket node by given socket id.
connected_client_list_t *mx_socket_list_find(connected_client_list_t *head, int sock_fd) {
    if (head == NULL) return NULL;
    for(connected_client_list_t *p = head; p != NULL; p = p->next) {
        if (p->sock_fd == sock_fd)
            return p;
    }
    return NULL;
}
