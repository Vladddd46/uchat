#include "client.h"

// Checks, wether user specified input correctly.
static void argv_validator(int argc, char **argv) {
    char *msg;

    if (argc != 3) {
        msg = "usage: ./client ip_address port\n";
        write(2, msg, (int)strlen(msg));
        exit(1);
    }

    int port = atoi(argv[2]);
    if (port == 0) {
        msg = "Invalid port number\n";
        write(2, msg, (int)strlen(msg));
        exit(1);
    }
}


int main(int argc, char **argv) {
    argv_validator(argc, argv);
    int port = atoi(argv[2]);

    /* <del>
     * Создаем сокет типа IPv4 для протокола TCP.
     */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    error("Error while creating socket", sockfd);

    /* <del>
     * Создаем структуру, в которой описываем информацию клинта:
     * (bzero - заполняет все нулями)
     * 1. адресс сервера, к которому хотим подключиться.
     * 2. версия айпи-адресса AF_INET = IPv4
     * 3. порт сервера.
     */
    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Local Host
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);

    /* <del>
     * Конектимся к серверу.
     * 1 - дескриптор сокета. 2 - указатель на структуру с информацией о сервере/клиента. 3. размер структуры.
     */

    int res = connect(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr));
    error("Error while connection", res);
    char* user_input = mx_strnew(200);

    scanf("%s", user_input);
    int len = mx_strlen(rsa_decode_password(user_input));
    write(sockfd, rsa_decode_password(user_input), len);

}





