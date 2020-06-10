#include "server.h"

// Retrieves operation from incomming packet.
static char *operation_determine(char *buffer) {
    char **splt_buffer      = mx_strsplit(buffer, '\n');
    char **operation_line   = mx_strsplit(splt_buffer[0], ' ');
    char *operation         = mx_string_copy(operation_line[1]);

    mx_del_strarr(&splt_buffer);
    mx_del_strarr(&operation_line);
    return operation;
}

// Retrieves login from incomming packet.
static char *login_determiner(char *packet) {
    char **splt_packet = mx_strsplit(packet, '\n');
    char **data_line   = mx_strsplit(splt_packet[1],   ' ');
    char *user_login   = mx_string_copy(data_line[1]);

    return user_login;
}

// Retrieves password from incomming packet.
static char *password_determiner(char *packet) {
    char **splt_packet    = mx_strsplit(packet, '\n');
    char **data_line      = mx_strsplit(splt_packet[1], ' ');
    char *user_password   = mx_string_copy(data_line[2]);

    return user_password;
}

int login (char *packet) {
    char *user_login    = login_determiner(packet);
    char *user_password = password_determiner(packet);

    printf("login: %s\npassword: %s\n", user_login, user_password);
    return 0;
}

void mx_client_process(int client_socket) {
    int n;
    char buffer[256];
    bzero(buffer,256);
    while(1) {
        n = read(client_socket, buffer, 255);
       
        char *operation = operation_determine(buffer);

        // login functionality.
        if (!strcmp(operation, "login")) {
            login(buffer);
        }
        printf("%s\n", buffer);
        // refreshing buffer.
        bzero(buffer,256);
    }
}
