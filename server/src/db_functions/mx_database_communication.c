#include "server.h"

/*
 * Receive packet and check, whether db should 
 * be modified. If true => modify db.
 * Forms new packet to send to client:
 * {to: client_login1; type: login; status_code: success}
 * {to: client_login2; from: client_login1; type: msg_update; data: "Hello"}
 */
char *mx_database_communication(char *packet) {
    // Code
    // ...
    // ...
    // ...
    // char *packet_type = packet_type_determiner(buffer);
    //             if (!strcmp(packet_type, "login")) {
    //                 status = login(*socket, buffer);
    //                 if (status  == LOGIN_SUCCESS) {
    //                     p->is_logged = true;
    //                 }
    //             }
    return NULL;
}

