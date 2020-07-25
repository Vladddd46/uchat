 #include "client.h"
 
 void mx_remake_chats(char *packet){
    char *length = get_value_by_key(packet,"LENGTH");
    int len = atoi(length);
    int i = 0;
    t_s_glade *gui = (t_s_glade *)malloc(sizeof(t_s_glade));
    gui->pack = packet;
    gui->pack = mx_strdup(gui->pack);
    gui->number = client_context->guinumber;
    GtkWidget *scroll = gtk_widget_get_parent(listbox);
    while (len > i && !gtk_events_pending()){
        gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_create_row, gui, 0);
        i++;
    }
 }
