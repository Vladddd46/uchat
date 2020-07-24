#include "server.h"

/*
 * Adds new node with socket (connection)
 * description in linked list.
 */
int mx_socket_list_add(connected_client_list_t *head, int new_sock_fd) {
    connected_client_list_t *p    = NULL;
    connected_client_list_t *prev = NULL;
    if (head == NULL) return -1;

    for(p = head; p != NULL; prev = p , p = p->next) {
        if (p->sock_fd == new_sock_fd) 
            return -3; // member exists
    }
    p = (connected_client_list_t *)malloc(sizeof(connected_client_list_t));
    if (p == NULL) return -1;
    p->sock_fd = new_sock_fd;
    p->is_logged = false;
    p->login = NULL;
    p->next = NULL;
    prev->next = p;
    return 0;
}
