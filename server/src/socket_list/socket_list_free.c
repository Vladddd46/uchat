#include "server.h"

// Frees linked list with sockets.
int mx_socket_list_free(connected_client_list_t *head) {
    if (head == NULL) return -1;
    connected_client_list_t *del = NULL;
    while (head->next != NULL) {
        del = head->next;
        head->next = del->next;
        if (del->login != NULL)
            free(del->login);
        free(del);
    }
    return 0;
}
