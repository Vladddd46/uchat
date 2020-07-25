#include "client.h"
               
void mx_logout_system(GtkWidget *widget, gpointer data){
    mx_close_window(editwindow);
    client_context->edit = 0;
    if (client_context->find == 1){
        gtk_widget_destroy(miniwindow);
        client_context-> find = 0;
    }
    if (client_context->sticker == 1){
        gtk_widget_destroy(stickerwindow);
        client_context-> sticker = 0;
    }
    gtk_widget_destroy(fixed);
    g_idle_add ((int (*)(void *))show_widget, window);
    fixed = gtk_fixed_new();
    char *packet_str = NULL;
    cJSON *packet     = cJSON_CreateObject();
    cJSON *json_value = cJSON_CreateString("logout_c");
    cJSON_AddItemToObject(packet, "TYPE", json_value);
    packet_str = cJSON_Print(packet);
    char *packet_with_prefix = packet_len_prefix_adder(packet_str);
    send(client_context->sockfd, packet_with_prefix, (int)strlen(packet_with_prefix), 0);
    gtk_container_add(GTK_CONTAINER(window), fixed);
    mx_main_menu();
}
