#include "server.h"

static void logout(connected_client_list_t **p) {
    connected_client_list_t *tmp = *p;
    tmp->is_logged = false;
}

/*
 * Receive packet and determines type of this packet. 
 * Modifies db if it`s needed and forms new packet,
 * which must be send to user (if he/she is online)
 * {to: client_login1; type: login; status_code: success}
 * {to: client_login2; from: client_login1; type: msg_update; data: "Hello"}
 */
char *mx_database_communication(char *packet, connected_client_list_t **p) {
    if (!strcmp(packet, "")) return NULL;
    char *packet_type      = get_value_by_key(packet, "TYPE");
    char *send_back_packet = NULL;

    if (!strcmp(packet_type, "login_c"))
        send_back_packet = login_system(packet); // 
    else if (!strcmp(packet_type, "reg_c"))
        send_back_packet = registration_system(packet); //
    else if (!strcmp(packet_type, "msg_c"))
        send_back_packet = mx_chat_render(packet);
    else if (!strcmp(packet_type, "find_user_c")) 
        send_back_packet = mx_find_user(packet);
    else if (!strcmp(packet_type, "add_msg_c"))
        send_back_packet = mx_add_message_by_id(packet);
    else if (!strcmp(packet_type, "add_contact_c"))
        send_back_packet = mx_add_contact(packet);
    else if (!strcmp(packet_type, "change_password_c"))
        send_back_packet = mx_change_password(packet);
    else if (!mx_strcmp(packet_type, "logout_c"))
        logout(p);
    free(packet_type);
    return send_back_packet;
}

