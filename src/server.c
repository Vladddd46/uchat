#include "uchat.h"
#include <netdb.h>
static void argv_validator(int argc, char **argv) {
    char *msg;
    int port;

    if (argc != 2) {
        msg = "usage: ./server PORT.\n";
        write(2, msg, (int)strlen(msg));
        exit(1);
    }
}

static void error(char *msg, int status) {
    if (status < 0) {
        perror(msg);
        exit(1);
    }
}


int main(int argc, char **argv) {
    argv_validator(argc, argv);
    int port = atoi(argv[1]);

    /* 
     * Creating socket, which works in IPv4
     * and has TCP type.
     */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    error("Creating socket error", sockfd);

    /* <del>
     * Создаем структуру, которая описывает адресс сервера:
     * - семейство адрессов (aka тип - IPv4/IPv6)
     * - сам адресс.
     */
    struct sockaddr_in serv_addr;
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family      = AF_INET;  // <del> семейство адрессов.
    serv_addr.sin_addr.s_addr = INADDR_ANY; // <del> адресс IPv4
    serv_addr.sin_port        = htons(port); // <del> номер порта

    /* <del>
     * связываем сокет с определенным адрессом, описанным в структуре.
     * serv_addr надо приводить к типу sockaddr (так надо)
     */
    int bind_status = bind(sockfd, (struct  sockaddr *)&serv_addr, sizeof(serv_addr));
    error("Bind error", bind_status);

    while(1) {
        int connect_status = connect(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr));
        error("Connect error", connect_status); 
    }
}


