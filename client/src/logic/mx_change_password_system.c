#include "client.h"
               
void mx_change_password_system(GtkWidget* widget, gpointer data){
    char *password = (char *)gtk_entry_get_text(GTK_ENTRY(widget));

    char *packet_str = NULL;
    cJSON *packet     = cJSON_CreateObject();
    cJSON *json_value = cJSON_CreateString("change_password_c");
    cJSON_AddItemToObject(packet, "TYPE", json_value);
    json_value = cJSON_CreateString(password);
    cJSON_AddItemToObject(packet, "TO", json_value);
    json_value = cJSON_CreateString(client_context->username);
    cJSON_AddItemToObject(packet, "LOGIN", json_value);
    packet_str = cJSON_Print(packet);
    char *packet_with_prefix = packet_len_prefix_adder(packet_str);
    send(client_context->sockfd, packet_with_prefix, (int)strlen(packet_with_prefix), 0);
    mx_close_window(editwindow);

}
