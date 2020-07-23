#include "client.h"

gboolean create_row_system(void *data) {
	char *packet = (char *)data;
	char *length = get_value_by_key(packet,"MSGLEN");
	if (length == NULL) 
	 	mx_null_error("6:create_row_system: get_value_by_key(length) retunred NULL");
	int len = atoi(length);

	client_context->allusers = get_value_by_key(packet,"ALLUSERS");
	if (client_context->allusers == NULL)
	 	mx_null_error("11:create_row_system: get_value_by_key(client_context->allusers) retunred NULL");
	free(length);

	t_s_glade *pack = (t_s_glade *)malloc(sizeof(t_s_glade));
	if (pack == NULL)
		mx_null_error("16:create_row_system: malloc retunred NULL");
	pack->pack = mx_string_copy(packet);
	pack->number = 0;
		

	GtkWidget *scrolll = gtk_widget_get_parent(listboxmess);
	gtk_widget_destroy(listboxmess);
	listboxmess = gtk_list_box_new(); 
	gtk_widget_set_name(listboxmess,"listboxmess");
	gtk_container_add(GTK_CONTAINER(scrolll), listboxmess);
	g_idle_add((int (*)(void *))show_widget, window);

	for (int i = 0; len > i; i++){
		gdk_threads_add_idle(create_message, pack);
	}
	return 0;
}

void create_row_system_new(client_context_t *client_context, char *packet) {
 char *length = get_value_by_key(packet,"MSGLEN");
 if (length == NULL)
 	mx_null_error("36:create_row_system_new: get_value_by_key retunred NULL");
 int len = atoi(length);
 client_context->allusers = get_value_by_key(packet,"ALLUSERS");
 if (client_context->allusers == NULL)
 	mx_null_error("40: create_row_system_new: get_value_by_key retunred NULL");
 	free(length);

 	t_s_glade *pack = (t_s_glade *)malloc(sizeof(t_s_glade));
 	if (pack == NULL)
 		mx_null_error("45: create_row_system_new: get_value_by_key retunred NULL");

	pack->pack = mx_string_copy(packet);
	pack->number = 0;

	g_idle_add ((int (*)(void *))show_widget, window);
	for (int i = 0; len > i; i++){
		gdk_threads_add_idle(create_message, pack);
	}
}
