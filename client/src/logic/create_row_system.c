#include "client.h"

void create_row_system(client_context_t *client_context, char *packet) {

 char *length = get_value_by_key(packet,"MSGLEN");
 int len = atoi(length);
 free(length);
 struct struct_type arg;
	arg.pack = packet;
	arg.number = 0;
	GtkWidget *scrolll = gtk_widget_get_parent(listboxmess);
	gtk_widget_destroy(listboxmess);
	listboxmess = gtk_list_box_new();
	gtk_widget_set_name(listboxmess,"listboxmess");
	gtk_container_add(GTK_CONTAINER(scrolll), listboxmess);
	gtk_widget_show_all(window);
	for (int i = 0; len > i; i++){
		create_message(newmessedgentry, arg);
		arg.number++;
	}
}
