#include "client.h"

gboolean mx_add_new_friend(GtkWidget *widget, gpointer data) {
   char  *login = g_object_get_data(G_OBJECT(widget),"name user");

  	cJSON *packet = cJSON_CreateObject();
    char  *packet_str = NULL;
  	cJSON *type = cJSON_CreateString("add_contact_c");
    cJSON *user = cJSON_CreateString(login);
    cJSON *nick = cJSON_CreateString(client_context->username);

    cJSON_AddItemToObject(packet, "TYPE", type);
    cJSON_AddItemToObject(packet, "USER", user);
    cJSON_AddItemToObject(packet, "TO", nick);
    packet_str = mx_string_copy(cJSON_Print(packet));
    char *packet_str1 =  packet_len_prefix_adder(packet_str);
    send(client_context->sockfd, mx_strdup(packet_str1), (int)strlen(packet_str1), 0);
    return FALSE;
}
