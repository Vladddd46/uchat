#include "server.h"

// Removes socket from linked list by gived socket id.
int socket_list_remove(socket_list_t *head, int sock_fd) {
    if (head == NULL) return -1;
    for(socket_list_t *p = head; p != NULL; p = p->next) {
        if (p->next != NULL && (p->next)->sock_fd == sock_fd) {
            socket_list_t *del = p->next;
            p->next = del->next;
            free(del);
            return 0;
        }
    }
    return -2; // not found
}