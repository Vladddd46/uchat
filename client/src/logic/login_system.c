#include "client.h"


void login_system(client_context_t *client_context, char *packet) {
	printf("Packet from server after login: %s\n\n", packet);
	char *length = get_value_by_key(packet,"LENGTH");
	client_context->username = get_value_by_key(packet,"TO");
	printf("%s\n",client_context->username ); 
	int len = atoi(length);
	free(length);
	t_s_glade *gui = (t_s_glade *)malloc(sizeof(t_s_glade));
	gui->pack = packet;
	gui->pack = mx_strdup(gui->pack);
	gui->number = 0;
	client_context->mas =mx_new_strarr(len +1000);
	gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, draw_message_menu, gui, 0);
	printf("%s\n","Start draw rows ");
	int i = 0;
	while (len > i && !gtk_events_pending()){
		gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, create_row, gui, 0);
		i++;
	}
}
 void remake_chats(char *packet){
 	//gtk_window_close(GTK_WINDOW(miniwindow));
 	char *length = get_value_by_key(packet,"LENGTH");
 	int len = atoi(length);
 	int i = 0;
 	t_s_glade *gui = (t_s_glade *)malloc(sizeof(t_s_glade));
	gui->pack = packet;
	gui->pack = mx_strdup(gui->pack);
	gui->number = 0;
	GtkWidget *scroll = gtk_widget_get_parent(listbox);
	// gtk_widget_destroy(listbox);
	// listbox = gtk_list_box_new(); 
	// gtk_widget_set_name(listbox,"listboxleft");
	// gtk_container_add(GTK_CONTAINER(scroll), listbox);
	//g_idle_add ((int (*)(void *))show_widget, window);
	g_signal_connect(listbox,"row-activated", G_CALLBACK(touch_room_signal), &client_context->sockfd);
	while (len > i && !gtk_events_pending()){
		gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, create_row, gui, 0);
		i++;
	}

 }

 void close_window(GtkWidget *widget){
 	gtk_window_close(GTK_WINDOW(widget));
 	g_idle_add ((int (*)(void *))show_widget, window);

 }

