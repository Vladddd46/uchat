#include "server.h"
#include <signal.h> 

static server_context_t ctx;
static pthread_mutex_t ctx_mutex = PTHREAD_MUTEX_INITIALIZER;
static bool quit = false; 

static void handle_sigchld(int sig) 
{
    printf("SIGCHLD handler\n");
    quit = true;
}

static void server_context_init(void)
{
    pthread_mutex_lock(&ctx_mutex);
    FD_ZERO (&ctx.read_descriptors);
    ctx.head.sock_fd = -1;
    ctx.head.is_logged = false;
    ctx.head.next = NULL;
    pthread_mutex_unlock(&ctx_mutex);
}

static void server_context_free(void)
{
    pthread_mutex_lock(&ctx_mutex);
    for (socket_list_t * p = ctx.head.next; p != NULL; p = p->next)
    {
        close(p->sock_fd);
    }
    socket_list_free (&ctx.head);
    pthread_mutex_unlock(&ctx_mutex);
}

static bool update_connections(fd_set * descriptors)
{
    char buffer[256];
    bool status = true;
    if (descriptors == NULL) return false;
    pthread_mutex_lock(&ctx_mutex);  
    for (socket_list_t * s = ctx.head.next; s != NULL; s = s->next)
    {
        if (recv(s->sock_fd, buffer, sizeof(buffer), MSG_PEEK | MSG_DONTWAIT) == 0)
        {
            printf("Connection on socket with fd %d was closed\n",s->sock_fd);
            close(s->sock_fd);
            FD_CLR(s->sock_fd, &ctx.read_descriptors);
            if (socket_list_remove(&ctx.head, s->sock_fd) < 0)
            {
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

static void *handle_server(void *param) 
{
    (void) param;
    int status;
    char buffer[256];
    int buf_len;
    bzero(buffer,256);
    fd_set read_descriptors;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    while(!quit) 
    {    
        update_connections(&read_descriptors);
        FD_SET(0,&read_descriptors);//stdin
       
        printf("thread loop step\n"); 
        tv.tv_sec = 1;
        status = select (FD_SETSIZE, &read_descriptors, NULL, NULL, &tv);

        if (status <= 0) continue;
        
        if (FD_ISSET(0, &read_descriptors))
        {
            int s = getchar();
            if (s == 'Q'){
                printf("Force QUIT\n");
                pid_t pid = getpid();
                kill(pid, SIGCHLD);
                sleep(1);
                continue;
            }
        }

        pthread_mutex_lock(&ctx_mutex);
        for (socket_list_t * p = ctx.head.next; p != NULL; p = p->next)
        {
            if (FD_ISSET(p->sock_fd, &read_descriptors)) 
            {
                buf_len = recv(p->sock_fd, buffer, 255, 0);
                printf("There was received %d bytes from socket %d\n",buf_len, p->sock_fd);
                //error("recv() error", buf_len);
                if (buf_len < 0) continue;
        #if 0
                char *packet_type = packet_type_determiner(buffer);
                if (!strcmp(packet_type, "login")) {
                    status = login(*socket, buffer);
                    if (status  == LOGIN_SUCCESS) {
                        p->is_logged = true;
                    }
                }
        #else
                p->is_logged = true;
                if (0){}
        #endif
                else {
                    for (socket_list_t * s = ctx.head.next; s != NULL; s = s->next)
                    {
                        if (s->is_logged) {
                            send(s->sock_fd, buffer, buf_len, 0);
                            printf("Sending of %d bytes\n",buf_len);
                        }
                    }                   
                }

                // refreshing buffer.
                bzero(buffer,256);
        #if 0
                free(packet_type);
        #endif
            }            
        }
        pthread_mutex_unlock(&ctx_mutex);
  
    }
    printf("handle_server thread was finished\n");
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
    listen(listening_socket, 10);

    signal(SIGCHLD, handle_sigchld);

    pthread_t server_thread;
    int err = pthread_create(&server_thread, NULL, handle_server, NULL);
    error("Can not create new thread", err);

    /* 
     * Loop, which waits for incomming requests.
     * accept() creates new socket, which will be used for certain client.
     * For communicating with client, two threads are created - listening and writing thread.
     */
    while(!quit) {
        struct sockaddr_in client;
        socklen_t client_len = sizeof(client);
        int newsockfd = accept(listening_socket, (struct sockaddr *)&client, &client_len);
        //error("Accept Error", newsockfd);
        if (newsockfd < 0) continue;
        pthread_mutex_lock(&ctx_mutex);
        int status = socket_list_add(&ctx.head, newsockfd);
        if (status == 0) {
            FD_SET(newsockfd, &ctx.read_descriptors);
            printf("new connection was accepted, fs = %d\n", newsockfd);
        }
        pthread_mutex_unlock(&ctx_mutex);
        error("Unable to add socket descriptor to the list", status);
    }
    sleep(2);
    server_context_free();
    printf("main thread was finished\n");
    exit(0);
}



