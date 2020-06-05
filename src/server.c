#include "uchat.h"

// Checks, wether user specified input correctly.
static void argv_validator(int argc) {
    char *msg;

    if (argc != 2) {
        msg = "usage: ./server PORT.\n";
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
        msg = "Invalid port number";
        write(2, msg, (int)strlen(msg));
        exit(1);
    }
    return port;
}

int main(int argc, char **argv) {
    argv_validator(argc);
    int port = get_port(argv);

    /* 
     * Creating socket, which works in IPv4
     * and has TCP type.
     */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    error("Creating socket error", sockfd);

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

    /* <del>
     * связываем сокет с определенным адрессом, описанным в структуре.
     * serv_addr надо приводить к типу sockaddr (так надо)
     */
    int bind_status = bind(sockfd, (struct  sockaddr *)&serv_addr, sizeof(serv_addr));
    error("Bind error", bind_status);

    /* <del> 
     * с помощью функции listen сервер заявляет о своем желании принимать запросы на установление соединения.
     * второй аргумент = лимит максимально возможных подключений.
     */
    listen(sockfd, 10);

    /* 
     * Цикл, который слушает подключения - если возникает подклчение,
     * функция accept создает новый файловый дескриптор для этого конкретного клиента (также создаю новый процесс для этого)
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


