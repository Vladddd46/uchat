#include "client.h"

gboolean mx_mini_button_release (GtkWidget *widget, GdkEventKey *event, gpointer data) {
  	char *editbuff = (char *)gtk_entry_get_text(GTK_ENTRY(minientry));
  	cJSON *packet = cJSON_CreateObject();
    char  *packet_str = NULL;
  	cJSON *type = cJSON_CreateString("find_user_c");
    cJSON *user = cJSON_CreateString(editbuff);
    cJSON *nick = cJSON_CreateString(client_context->username);

    cJSON_AddItemToObject(packet, "TYPE", type);
    cJSON_AddItemToObject(packet, "USER", user);
    cJSON_AddItemToObject(packet, "TO", nick);
    packet_str = mx_string_copy(cJSON_Print(packet));
    packet_str =  packet_len_prefix_adder(packet_str);
    send(client_context->sockfd, packet_str, (int)strlen(packet_str), 0);
    return FALSE;
}
