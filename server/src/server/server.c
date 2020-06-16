#include "server.h"

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

int main(int argc, char **argv) {
    argv_validator(argc);
    int port             = get_port(argv);
    int listening_socket = listening_socket_init(port);
    database_init();
    
    /* 
     * Making sockfd listening for incomming requests.
     * The second argument - number of max. number of requests. 
     * If more - incomming requests must que.
     */
    listen(listening_socket, 10);

    /* 
     * Loop, which waits for incomming requests.
     * accept() creates new socket, which will be used for certain client.
     * For communicating with client, two threads are created - listening and writing thread.
     */
    while(1) {
        struct sockaddr_in client;
        socklen_t client_len = sizeof(client);
        int newsockfd = accept(listening_socket, (struct sockaddr *)&client, &client_len);
        error("Accept Error", newsockfd);

        pthread_t client_thread;
        int err = pthread_create(&client_thread, NULL, handle_client, &newsockfd);
        error("Can not create new thread", err);
    }
}


