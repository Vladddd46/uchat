#include "server.h"
#include <signal.h> 

/*
 * Declaration of structure, which contains  server context.
 * a. fd_set read_descriptors - bitarray, which contains all conected client sockets.
 *    (it is needed for select)
 * b. socket_list_t list - linked list of connected client sockets.
 */
static server_context_t ctx;

// Initialize mutex with default settings.
static pthread_mutex_t ctx_mutex = PTHREAD_MUTEX_INITIALIZER;

// if quit == true, server exits.
static bool quit = false; 

static void handle_sigchld(int sig)  {
    printf("SIGCHLD handler\n");
    quit = true;
}

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
    for (socket_list_t *p = ctx.head.next; p != NULL; p = p->next) {
        close(p->sock_fd);
    }
    socket_list_free(&ctx.head);
    pthread_mutex_unlock(&ctx_mutex);
}

/*
 * Checks, whether socket is closed.
 * if true => deletes socket from socket list.
 */
static bool update_connections(fd_set *descriptors) {
    char buffer[256];
    bool status = true;
    if (descriptors == NULL) return false;

    pthread_mutex_lock(&ctx_mutex);  
    for (socket_list_t *s = ctx.head.next; s != NULL; s = s->next) {
        if (recv(s->sock_fd, buffer, sizeof(buffer), MSG_PEEK | MSG_DONTWAIT) == 0) {
            printf("Connection on socket with fd %d was closed\n", s->sock_fd);
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

// Checks, wether user specified input correctly.
static void argv_validator(int argc) {
    char *msg;

    if (argc != 2) {
        msg = "usage: ./server PORT\n";
        write(2, msg, (int)strlen(msg));
        exit(1);
    }
}

/*
 * Checks, whather user sepcified port number correctly.
 * If wrong port number - error msg prints + exit.
 * In case of success  - returns <int> port number.
 */
static int get_port(char **argv) {
    int port = atoi(argv[1]);
    char *msg;

    if (port == 0) {
        msg = "Invalid port number\n";
        write(2, msg, (int)strlen(msg));
        exit(1);
    }
    return port;
}

// Determines type of packet.
static char *packet_type_determiner(char *buffer) {
    char *packet_type = NULL;
    cJSON *parsed_str = cJSON_Parse(buffer);
    char *msg = "Json Parsing error\n";
    if (parsed_str == NULL) {
        write(2, msg, (int)strlen(msg));
        exit(1);
    }
    cJSON *type = cJSON_GetObjectItemCaseSensitive(parsed_str, "TYPE");
    if (cJSON_IsString(type) && (type->valuestring != NULL)) {
        packet_type = mx_string_copy(type->valuestring);
    }
    cJSON_Delete(parsed_str);

    return packet_type;
}

static void *handle_server(void *param) {
    (void)param;
    int status;
    char buffer[256];
    int buf_len;
    bzero(buffer,256);
    fd_set read_descriptors;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    while(!quit) {    
        update_connections(&read_descriptors);

        // <del> добавляем stdin в список отслеживаемых дескрипторов.
        FD_SET(0,&read_descriptors); 
       
        printf("wait for incomming packets...\n"); 
        tv.tv_sec = 1;
        status = select(FD_SETSIZE, &read_descriptors, NULL, NULL, &tv);

        // if no sockets are availabe => continue loop.
        if (status <= 0) continue;
        
        // if stdin is active => checking it`s input. if input == 'q', stop server. // debug 
        if (FD_ISSET(0, &read_descriptors)) {
            int s = getchar();
            if (s == 'q') {
                printf("Force QUIT\n");
                pid_t pid = getpid();
                kill(pid, SIGCHLD);
                sleep(1);
                continue;
            }
        }

        pthread_mutex_lock(&ctx_mutex);
        /*
         * Going through each opened socket and determine, whether socket is active.
         * if socket is active => receive packet from it => alalyze this packet =>
         * change db if it`s needed => if this packet must be sent to another user => form new packet, 
         * go through linked list with opened sockets(connected clients) and check,
         * whether socket node has the same attribute(user_login) as specified in new packet.
         * if node was found -> send packet to socket, specified in it. Otherwise, just 
         * change db depending on packet => as user is getting logged, all new data retrieves 
         * from db.
         */
        for (socket_list_t *p = ctx.head.next; p != NULL; p = p->next) {
            if (FD_ISSET(p->sock_fd, &read_descriptors)) {
                buf_len = recv(p->sock_fd, buffer, 255, 0);
                printf("There was received %d bytes from socket %d\n", buf_len, p->sock_fd); // Debug.
                if (buf_len < 0) continue;

                // Modify db and forms packet, which must be send to specified in packet client.
                char *send_packet = mx_database_communication(buffer);
                /* Retrieves user`s login from packet. Packet will be send on this login, 
                 * if user with this login is connected to the server.
                 */
                char *client_login = login_determiner(send_packet);

                p->is_logged = true;
                for (socket_list_t *s = ctx.head.next; s != NULL; s = s->next) {
                    if (s->is_logged) { // && !strcmp(client_login, s->login)
                        send(s->sock_fd, buffer, buf_len, 0); // send_packet must be sent
                        printf("Sending of %d bytes\n",buf_len); // Debug.
                    }
                }                    
                // refreshing buffer.
                bzero(buffer,256);
                // free(send_packet);
                // free(client_login)
            }            
        }
        pthread_mutex_unlock(&ctx_mutex);
    }
    printf("handle_server thread was finished\n"); // Debug.
    return NULL;
}


int main(int argc, char **argv) {
    argv_validator(argc);
    int port             = get_port(argv);
    int listening_socket = listening_socket_init(port);
    database_init();
    server_context_init();

    /* 
     * Making sockfd listening for incomming requests.
     * The second argument - number of max. number of requests. 
     * If more - incomming requests must que.
     */
    listen(listening_socket, 128);

    signal(SIGCHLD, handle_sigchld);

    pthread_t server_thread;
    int err = pthread_create(&server_thread, NULL, handle_server, NULL);
    error("Can not create new thread", err);

    /* 
     * Loop, which waits for incomming requests.
     * accept() creates new socket, which will be used for certain client.
     * Place new socket in linked list of opening sockets and in fd_set array. 
     */
    while(!quit) {
        struct sockaddr_in client;
        socklen_t client_len = sizeof(client);
        int newsockfd = accept(listening_socket, (struct sockaddr *)&client, &client_len);

        // if acception error, continue the loop.
        if (newsockfd < 0) continue;

        /*
         * When new connection comes in, created socket is getting placed in 
         * linked list with opening sockets. If socket was successfully placed in llist,
         * it is also getting placed in fd_set bitarray (it`s needed for select.)
         * *Mutex is used because `ctx.head` is also used in handle_server thread.
         */
        pthread_mutex_lock(&ctx_mutex);
        int status = socket_list_add(&ctx.head, newsockfd);
        if (status == 0) {
            FD_SET(newsockfd, &ctx.read_descriptors);
            printf("New connection was accepted, socket = %d\n", newsockfd);
        }
        pthread_mutex_unlock(&ctx_mutex);
        error("Unable to add socket descriptor to the list", status);
    }
    sleep(2);
    server_context_free();
    printf("Main thread was finished\n");
    exit(0);
}