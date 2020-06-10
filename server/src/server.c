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

/*
 * Describes address of server.
 * Returns structure sockaddr_in with description.
 */
static struct sockaddr_in serv_address_description(int port) {
    /* <del>
     * Создаем структуру, которая описывает адресс сервера:
     * bzero -  заполняет структуру \0
     * - семейство адрессов (aka тип - IPv4/IPv6)
     * - сам адресс.
     */
    struct sockaddr_in serv_addr;
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;           // <del> семейство адрессов.
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // <del> адресс IPv4 PS. INADDR_ANY это вроже любой доступный локальный адресс (это не точно)
    serv_addr.sin_port        = htons(port);       // <del> номер порта
    return serv_addr;
}

int main(int argc, char **argv) {
    argv_validator(argc);
    int port = get_port(argv);
    
    /* 
     * Creating listening socket, which works in IPv4
     * and has TCP type.
     */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    error("Creating socket error", sockfd);

    // Getting structure with server address description.
    struct sockaddr_in serv_addr = serv_address_description(port);

    /* 
     * Binding listening socket with certain address, describes in sructure serv_addr.
     * serv_addr must be cast to sockaddr.
     */
    int bind_status = bind(sockfd, (struct  sockaddr *)&serv_addr, sizeof(serv_addr));
    error("Bind error", bind_status);

    /* 
     * Making sockfd listening for incomming requests.
     * The second argument - number of max. number of requests. 
     * If more - incomming requests must que.
     */
    listen(sockfd, 10);

    /* 
     * Loop, which waits for incomming requests.
     * accept() creates new socket, which will be used for certain client.
     * For communicating with client, new process is created.
     */
    while(1) {
        struct sockaddr_in client;
        socklen_t client_len = sizeof(client);
        int newsockfd = accept(sockfd, (struct sockaddr *)&client, &client_len);
        error("Accept Error", newsockfd);

        int pid = fork();
        error("Fork Error", pid);

        if (pid == CHILD) {
            close(sockfd);
            mx_client_process(newsockfd);
            exit(0);
        }
        else {
            close(newsockfd);
        }
    }
}


