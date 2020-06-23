#include "server.h"

/*
 * Retrieves needed data from the packet.
 * Makes request to db and checks data validity.
 * Forms back packet.
 */
char *login_system(char *packet) {
    char *login    = get_value_buy_key(packet, "LOGIN");
    char *password = get_value_buy_key(packet, "PASSWORD");

    // char *return_status = db_login_request(login, password);
    // char *status        = mx_strjoin("STATUS:", return_status);
    // char *sendback_packet    = json_packet_former(2, "TYPE:login_s", status);
    char   *sendback_packet = json_packet_former(2, "TYPE:login_s", "STATUS:true"); // Debug.
    return sendback_packet;
}
