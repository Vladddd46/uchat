#include "server.h"

// static char *msg_former(int status) {
//     char *msg = NULL;

//     if (status == 1)
//         msg = "MSG:OK";
//     else if (status == 2)
//         msg = "MSG:User with such login is already exists";
//     else if (status == 3)
//         msg = "MSG:User with such nickname is already exists";
//     return msg;
// }

// static char *status_converter(int return_status) {
//     if (return_status == 1)
//         return "STATUS:true";
//     return "STATUS:false";
// }

char *registration_system(char *packet) {
    char *login    = get_value_by_key(packet, "LOGIN");
    char *password = get_value_by_key(packet, "PASSWORD");
    char *nickname = get_value_by_key(packet, "NICKNAME");

    // int  return_status     = db_reg_request(login, password, nickname);
    // char *status           = status_converter(return_status);
    // char *msg              = msg_former(return_status);
    // char *sendback_packet  = json_packet_former(2, "TYPE:reg_s", status, msg);
    char *not_terminated_packet = json_packet_former(2, "TYPE:reg_s", "STATUS:success"); // Debug.
    char *sendback_packet       = mx_char_to_str_add(not_terminated_packet, 20);
    free(not_terminated_packet);
    return sendback_packet;
}
