#include "client.h"

void create_row_system(client_context_t *client_context, char *packet) {
 char *length = get_value_by_key(packet,"MSGLEN");
 int len = atoi(length);
 client_context->allusers = get_value_by_key(packet,"ALLUSERS");
 free(length);
 t_s_glade *pack = (t_s_glade *)malloc(sizeof(t_s_glade));
	pack->pack = packet;
	pack->pack = mx_strdup(pack->pack);
	pack->number = 0;
	GtkWidget *scrolll = gtk_widget_get_parent(listboxmess);
	gtk_widget_destroy(listboxmess);
	listboxmess = gtk_list_box_new(); 
	gtk_widget_set_name(listboxmess,"listboxmess");
	gtk_container_add(GTK_CONTAINER(scrolll), listboxmess);
	g_idle_add ((int (*)(void *))show_widget, window);
	for (int i = 0; len > i; i++){ 
		printf("%s\n",">>>>>>>>" );
		gdk_threads_add_idle(create_message, pack);
	}
}

void create_row_system_new(client_context_t *client_context, char *packet) {
 char *length = get_value_by_key(packet,"MSGLEN");
 int len = atoi(length);
 client_context->allusers = get_value_by_key(packet,"ALLUSERS");
 free(length);
 t_s_glade *pack = (t_s_glade *)malloc(sizeof(t_s_glade));
	pack->pack = mx_strdup(packet);
	pack->number = 0;
	GtkWidget *scrolll = gtk_widget_get_parent(listboxmess);

	g_idle_add ((int (*)(void *))show_widget, window);
	for (int i = 0; len > i; i++){
		gdk_threads_add_idle(create_message, pack);
	}
}
