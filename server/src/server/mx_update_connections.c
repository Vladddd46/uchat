#include "server.h"

/*
 * Checks, whether client closed the connection.
 * if true => deletes socket from server context.
 */
bool mx_update_connections(fd_set *descriptors, 
                           server_context_t ctx, 
                           pthread_mutex_t ctx_mutex) {
    char buffer[256];
    bool status = true;
    if (descriptors == NULL) return false;

    pthread_mutex_lock(&ctx_mutex);  
    for (connected_client_list_t *s = ctx.head.next; s != NULL; s = s->next) {
        if (recv(s->sock_fd, buffer, sizeof(buffer), MSG_PEEK | MSG_DONTWAIT) == 0) {
            printf("Connection on socket with socket fd %d was closed\n", s->sock_fd);
            close(s->sock_fd);
            FD_CLR(s->sock_fd, &ctx.read_descriptors);
            if (socket_list_remove(&ctx.head, s->sock_fd) < 0) {
                status = false;
            }
        }
    }
    *descriptors = ctx.read_descriptors;    
    pthread_mutex_unlock(&ctx_mutex);
    return status;
}

