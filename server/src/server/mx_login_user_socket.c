#include "server.h"

// Does the login of connected socket.
void mx_login_user_socket(connected_client_list_t *p,
                         char *send_packet, 
                         char **receivers) {
    if (mx_strcmp(send_packet, "") == 0)
        return;

    if ((!strcmp(get_value_by_key(send_packet, "TYPE"), "login_s") 
        || !strcmp(get_value_by_key(send_packet, "TYPE"), "reg_s"))) {

        if (!strcmp(get_value_by_key(send_packet, "STATUS"), "success")) {
            p->login = mx_string_copy(receivers[0]);
            p->is_logged = true;
        }
    }
}
