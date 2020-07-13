#include "client.h"

/*
 * Analyze the incomming packet and 
 * depending on it`s type calls the func.
 */
void mx_received_packet_analyzer(char *packet_type, char *packet, 
                                 client_context_t *client_context) {

    if (!strcmp(packet_type, "reg_s"))
        registration_system(client_context->sockfd, packet);
    else if (!strcmp(packet_type, "login_s"))
        login_system(client_context, packet);
    else if (!strcmp(packet_type, "find_user_s"))
        printf("%s\n", "find_user packet receive");
    else if (!strcmp(packet_type, "msg_s"))
        create_row_system(client_context, packet);
}

