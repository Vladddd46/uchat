#include "server.h"

// Determines type of packet.
static char *packet_type_determiner(char *buffer) {
    char *packet_type = NULL;
    cJSON *parsed_str = cJSON_Parse(buffer);
    char *msg = "Json Parsing error\n";
    if (parsed_str == NULL) {
        write(2, msg, (int)strlen(msg));
        exit(1);
    }
    cJSON *type = cJSON_GetObjectItemCaseSensitive(parsed_str, "TYPE");
    if (cJSON_IsString(type) && (type->valuestring != NULL)) {
        packet_type = mx_string_copy(type->valuestring);
    }
    cJSON_Delete(parsed_str);
    return packet_type;
}

/*
 * Receive packet and check, type of this packet. 
 * Modifies db if it`s needed and forms new packet,
 * which must be send to user (if he/she is online)
 * {to: client_login1; type: login; status_code: success}
 * {to: client_login2; from: client_login1; type: msg_update; data: "Hello"}
 */
char *mx_database_communication(char *packet) {
    char *packet_type = packet_type_determiner(packet);
    // char *back_msg;

    if (!strcmp(packet_type, "login_c")) {
        printf("\n\nLogin packet received\n\n");
        // back_msg = login();
    }
    else if (!strcmp(packet_type, "reg_c")) {
        printf("\n\nReg packet received\n\n");
        // back_msg = registration();
    }
    else if (!strcmp(packet_type, "find_user_c")) {
        printf("\n\nfind_user_c packet received\n\n");
        // back_msg = find_user();
    }
    else if (!strcmp(packet_type, "msg_c")) {
        printf("\n\nmsg_c packet received\n\n");
        // back_msg = msg();
    }
    return NULL;
    // return back_msg;
}

