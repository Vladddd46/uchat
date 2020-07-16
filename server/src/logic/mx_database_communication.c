#include "server.h"

static int mx_callback(void* not_used, int argc, char** argv, char** az_con_name) {
    for(int i = 0; i < argc; i++) {
        printf("%s: %s\n", az_con_name[i], argv[i]);
    }
    return 0;
}
/*
 * Receive packet and determines type of this packet. 
 * Modifies db if it`s needed and forms new packet,
 * which must be send to user (if he/she is online)
 * {to: client_login1; type: login; status_code: success}
 * {to: client_login2; from: client_login1; type: msg_update; data: "Hello"}
 */
char *mx_database_communication(char *packet) {
    // mx_printstr("\nGet here printstr\n\n");
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
    else if (!strcmp(packet_type, "msg_c")) {
        printf("\n\nmsg_c packet received\n\n");
        // printf("%s\n", packet);
        send_back_packet = mx_get_message(packet);
    }
    else if (!strcmp(packet_type, "find_user_c")) {
        printf("\n\nfind_user_c packet received\n\n");
        send_back_packet = mx_find_user(packet);
        printf("send_back_packet %s\n", send_back_packet);
    }
    else if (!strcmp(packet_type, "add_msg_c")) {
        printf("\n\nmsg_c packet received\n\n");
        send_back_packet = mx_add_message_by_id(packet);
        // send_back_packet = msg();
    }
    else if (!strcmp(packet_type, "add_contact_c")) {
        printf("\n\nmsg_c packet received\n\n");
        send_back_packet = mx_add_contact(packet);
        // send_back_packet = msg();
    }

    // free(packet_type); // почему - то иногда выдает ошибку malloc error
    printf("Finder %s\n", send_back_packet);
    return send_back_packet;
}

