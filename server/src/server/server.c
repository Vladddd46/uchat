#include "server.h"
#include <signal.h> 

/*
 * Declaration of structure, which contains  server context.
 * a. fd_set read_descriptors - bitarray, which contains 
 *    all conected client sockets. (it is needed for select)
 * b. connected_client_list_t list - linked list of connected client sockets.
 */
static server_context_t ctx;
// Initialize mutex with default settings.
static pthread_mutex_t ctx_mutex = PTHREAD_MUTEX_INITIALIZER;
// if quit == true, server exits.
static bool quit = false; 

static void server_context_init(void) {
    pthread_mutex_lock(&ctx_mutex);
    FD_ZERO (&ctx.read_descriptors);
    ctx.head.sock_fd = -1;
    ctx.head.is_logged = false;
    ctx.head.next = NULL;
    pthread_mutex_unlock(&ctx_mutex);
}

static void server_context_free(void) {
    pthread_mutex_lock(&ctx_mutex);
    for (connected_client_list_t *p = ctx.head.next; p != NULL; p = p->next) {
        close(p->sock_fd);
    }
    mx_socket_list_free(&ctx.head);
    pthread_mutex_unlock(&ctx_mutex);
}

/*
 * Checks, whether client closed the connection.
 * if true => deletes socket from server context.
 */
static bool update_connections(fd_set *descriptors) {
    char buffer[256];
    bool status = true;
    if (descriptors == NULL) return false;

    pthread_mutex_lock(&ctx_mutex);  
    for (connected_client_list_t *s = ctx.head.next; s != NULL; s = s->next) {
        if (recv(s->sock_fd, buffer, sizeof(buffer), MSG_PEEK | MSG_DONTWAIT) == 0) {
            printf("Connection on socket with socket fd %d was closed\n", s->sock_fd);
            close(s->sock_fd);
            FD_CLR(s->sock_fd, &ctx.read_descriptors);
            if (mx_socket_list_remove(&ctx.head, s->sock_fd) < 0) {
                status = false;
            }
        }
    }
    *descriptors = ctx.read_descriptors;    
    pthread_mutex_unlock(&ctx_mutex);
    return status;
}

static char **mx_packet_receivers_determine(char *packet) {
    char *logins = mx_string_copy(get_value_by_key(packet, "TO"));
    char **receivers = mx_strsplit(logins, ' ');
    // free(logins);
    return receivers;
}


static void *handle_server(void *param) {
    int status;
    fd_set read_descriptors;
    struct timeval tv = wait_time(1, 0);

    while(true) {    
        update_connections(&read_descriptors);
        printf("wait for incomming packets...\n");
        status = select(FD_SETSIZE, &read_descriptors, NULL, NULL, &tv);
        if (status <= 0) continue;
        
        pthread_mutex_lock(&ctx_mutex);
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
        for (connected_client_list_t *p = ctx.head.next; p != NULL; p = p->next) {
            if (FD_ISSET(p->sock_fd, &read_descriptors)) {
                char *packet = packet_receive(p->sock_fd);
                if (packet == NULL || !mx_strcmp("", packet)) {
                    printf("%s\n", "packet is null");
                    break;
                    mx_null_value_error("handle_server");
                }
                char *logout = get_value_by_key(packet, "TYPE");
                if (logout == NULL) {
                    printf("LOGOUT NULL");
                    break;
                }
                if (!mx_strcmp(logout, "logout_c")) {
                    p->is_logged = false;
                    break;
                }

                printf("packetych =>>> %s\n", packet);
                char *send_packet = mx_database_communication(packet);
                if (send_packet == NULL) break;
                printf("sendback packetych = >> %s\n", send_packet);
                char *logins = get_value_by_key(send_packet, "TO");
                char **receivers = mx_strsplit(logins, ' ');

                mx_login_user_socket(p, send_packet, receivers);
                char *send_back_packet_prefixed =  packet_len_prefix_adder(send_packet);
 
                for (connected_client_list_t *s = ctx.head.next; s != NULL; s = s->next) {
                    if (s->is_logged && mx_str_in_arr(s->login, receivers))
                        send(s->sock_fd, send_back_packet_prefixed, (int)strlen(send_back_packet_prefixed), 0);
                }          
            }            
        }
        pthread_mutex_unlock(&ctx_mutex);
    }
    return NULL;
}


/* 
 * Loop, which waits for incomming requests.
 * accept() creates new socket, which will be used for certain client.
 * Place new socket in linked list of opening sockets and in fd_set array. 
 */
int main(int argc, char **argv) {
    mx_argv_validator(argc);
    int port             = mx_get_port(argv);
    int listening_socket = mx_listening_socket_init(port);

    mx_database_init();
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
        int status = mx_socket_list_add(&ctx.head, newsockfd);
        if (status == 0)
            FD_SET(newsockfd, &ctx.read_descriptors);
        pthread_mutex_unlock(&ctx_mutex);
        error("Unable to add socket descriptor to the list", status);
    }
}
