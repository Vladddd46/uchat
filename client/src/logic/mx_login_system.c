#include "client.h"

void mx_login_system(client_context_t *client_context, char *packet) {
    char *length = get_value_by_key(packet,"LENGTH");
    client_context->username = get_value_by_key(packet,"TO");
    int len = atoi(length);
    free(length);
    t_s_glade *gui = (t_s_glade *)malloc(sizeof(t_s_glade));
    gui->pack = packet;
    gui->pack = mx_strdup(gui->pack);
    gui->number = 0;
    client_context->mas = mx_new_strarr(len + 1000);
    gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_draw_message_menu, gui, 0);
    int i = 0;
    while (len > i && !gtk_events_pending()){
        gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_create_row, gui, 0);
        i++;
    }
}
