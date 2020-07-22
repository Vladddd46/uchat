#include "server.h"
#include <signal.h> 

/*
 * Declaration of structure, which contains  server context.
 * a. fd_set read_descriptors - bitarray, which contains 
 *    all conected client sockets. (it is needed for select)
 * b. connected_client_list_t list - linked list of connected client sockets.
 */
static server_context_t ctx;
static pthread_mutex_t ctx_mutex = PTHREAD_MUTEX_INITIALIZER;

static void server_context_init(void) {
    pthread_mutex_lock(&ctx_mutex);
    FD_ZERO (&ctx.read_descriptors);
    ctx.head.sock_fd = -1;
    ctx.head.is_logged = false;
    ctx.head.next = NULL;
    pthread_mutex_unlock(&ctx_mutex);
}



static char **mx_packet_receivers_determine(char *packet) {
    char *logins     = get_value_by_key(packet, "TO");
    if (logins == NULL)
        logins = " ";
    char **receivers = mx_strsplit(logins, ' ');

    free(logins);
    return receivers;
}



static int handle_connection(connected_client_list_t *p, fd_set read_descriptors) {
    if (FD_ISSET(p->sock_fd, &read_descriptors)) {
        char *packet = packet_receive(p->sock_fd);
        if (packet == NULL) return 1;
        char *send_packet = mx_database_communication(packet, &p);
        if (send_packet == NULL) return 1;
        char **receivers  = mx_packet_receivers_determine(send_packet);
        mx_login_user_socket(p, send_packet, receivers);

        for (connected_client_list_t *s = ctx.head.next; s != NULL; s = s->next) {
            if (s->is_logged && mx_str_in_arr(s->login, receivers))
            mx_send(s->sock_fd, send_packet);
        }          
        free(send_packet);
        free(packet);
    }
    return 0;          
}



/*
 * Going through each opened socket and determine, whether socket is active.
 * if true => receive packet from socket => alalyze this packet =>
 * change db if it`s needed and form new packet to send.
 * Go through linked list with opened sockets(connected clients) and check,
 * whether socket node has the same attribute(user_login) as specified in new packet.
 * if node was found -> send packet to socket, specified in it. Otherwise, just 
 * change db depending on packet => as user is getting logged, all new data retrieves 
 * from db.
 */
static void *handle_server(void *param) {
    int status;
    fd_set read_descriptors;
    struct timeval tv = wait_time(1, 0);

    while(true) {    
        mx_update_connections(&read_descriptors, ctx, ctx_mutex);
        printf("wait for incomming packets...\n");
        status = select(FD_SETSIZE, &read_descriptors, NULL, NULL, &tv);
        if (status <= 0) continue;
        pthread_mutex_lock(&ctx_mutex);
        for (connected_client_list_t *p = ctx.head.next; p != NULL; p = p->next) {
            if (handle_connection(p, read_descriptors))
                break;
        }
        pthread_mutex_unlock(&ctx_mutex);
    }
    printf("handle_server thread was finished\n"); // Debug.
    return NULL;
}



/* 
 * Loop, which waits for incomming requests.
 * accept() creates new socket, which will be used for certain client.
 * Place new socket in linked list of opening sockets and in fd_set array. 
 */
int main(int argc, char **argv) {
    argv_validator(argc);
    int port             = get_port(argv);
    int listening_socket = listening_socket_init(port);
    database_init();
    server_context_init();
    listen(listening_socket, 128);
    pthread_t server_thread;
    int err = pthread_create(&server_thread, NULL, handle_server, NULL);
    error("Can not create new thread", err);

    while(true) {
        struct sockaddr_in client;
        socklen_t client_len = sizeof(client);
        int newsockfd = accept(listening_socket, (struct sockaddr *)&client, &client_len);
        if (newsockfd < 0) continue;
        pthread_mutex_lock(&ctx_mutex);
        int status = socket_list_add(&ctx.head, newsockfd);
        if (status == 0)
            FD_SET(newsockfd, &ctx.read_descriptors);
        pthread_mutex_unlock(&ctx_mutex);
        error("Unable to add socket descriptor to the list", status);
    }
}
