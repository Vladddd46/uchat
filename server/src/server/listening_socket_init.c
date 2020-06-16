#include "server.h"

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

/*
 * Initialize listening socket.
 * create socket -> describe address -> bind socket.
 * Returns created socket.
 */
int listening_socket_init(int port) {
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

    return sockfd;
}

