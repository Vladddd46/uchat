#include "client.h"

void create_row_system_new(client_context_t *client_context, char *packet) {
	// GtkListBoxRow *indexroww = gtk_list_box_get_row_at_index (GTK_LIST_BOX(listbox),client_context->indexrow);
	// GList *gl = gtk_container_get_children(GTK_CONTAINER(indexroww));
 //    GtkGrid *gridd = gl->data;
	// GtkWidget *chatn = gtk_grid_get_child_at(gridd,1,0);
	// char *chatnam = (char *)gtk_label_get_text(GTK_LABEL(chatn));
		char *chatid = get_value_by_key(packet,"CHATID");
		if (!mx_strcmp(chatid,client_context->mas[client_context->indexrow])) {
			write(1, "\a", 1);
			char *length = get_value_by_key(packet,"MSGLEN");
			int len = atoi(length);
			client_context->allusers = get_value_by_key(packet,"ALLUSERS");
			t_s_glade *pack = (t_s_glade *)malloc(sizeof(t_s_glade));
			pack->pack = mx_string_copy(packet);
			pack->number = 0;
			g_idle_add ((int (*)(void *))show_widget, window);
			for (int i = 0; len > i; i++)
				gdk_threads_add_idle(create_message, pack);
		}

}
