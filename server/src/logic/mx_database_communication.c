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
    char *packet_type      = get_value_by_key(packet, "TYPE");
    char *send_back_packet = NULL;

    if (!strcmp(packet_type, "login_c"))
        send_back_packet = login_system(packet);
    else if (!strcmp(packet_type, "reg_c"))
        send_back_packet = registration_system(packet);
    else if (!strcmp(packet_type, "msg_c"))
        send_back_packet = mx_get_message(packet);
    else if (!strcmp(packet_type, "find_user_c")) 
        send_back_packet = mx_find_user(packet);
    else if (!strcmp(packet_type, "add_msg_c"))
        send_back_packet = mx_add_message_by_id(packet);
    else if (!strcmp(packet_type, "add_contact_c"))
        send_back_packet = mx_add_contact(packet);

    return send_back_packet;
}

