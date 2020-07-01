#include "server.h"

/*
 * Receive packet and determines type of this packet. 
 * Modifies db if it`s needed and forms new packet,
 * which must be send to user (if he/she is online)
 * {to: client_login1; type: login; status_code: success}
 * {to: client_login2; from: client_login1; type: msg_update; data: "Hello"}
 */
char *mx_database_communication(char *packet) {
    if (!strcmp(packet, ""))
        return NULL;
    char *packet_type = get_value_by_key(packet, "TYPE");
    char *send_back_packet = NULL;

    if (!strcmp(packet_type, "login_c")) {
        printf("\n\nLogin packet received\n\n");
        send_back_packet = login_system(packet);
    }
    else if (!strcmp(packet_type, "reg_c")) {
        printf("\n\nReg packet received\n\n");
        send_back_packet = registration_system(packet);
    }
    else if (!strcmp(packet_type, "find_user_c")) {
        printf("\n\nfind_user_c packet received\n\n");
        // send_back_packet = find_user();
    }
    else if (!strcmp(packet_type, "msg_c")) {
        printf("\n\nmsg_c packet received\n\n");
        // send_back_packet = msg();
    }
    // free(packet_type); // почему - то иногда выдает ошибку malloc error
    return send_back_packet;
}

