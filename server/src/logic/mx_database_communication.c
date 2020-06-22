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
    if (!strcmp(packet, ""))
        return NULL;
    char *packet_type = packet_type_determiner(packet);
    char *send_back_packet;

    if (!strcmp(packet_type, "login_c")) {
        printf("\n\nLogin packet received\n\n");
        // send_back_packet = login();
    }
    else if (!strcmp(packet_type, "reg_c")) {
        printf("\n\nReg packet received\n\n");
        // send_back_packet = registration();
    }
    else if (!strcmp(packet_type, "find_user_c")) {
        printf("\n\nfind_user_c packet received\n\n");
        // send_back_packet = find_user();
    }
    else if (!strcmp(packet_type, "msg_c")) {
        printf("\n\nmsg_c packet received\n\n");
        // send_back_packet = msg();
    }

    free(packet_type);
    return NULL;
    // return send_back_packet;
}

