#include "client.h"

void mx_create_row_system_new(client_context_t *client_context, char *packet) {
	char *chatid = get_value_by_key(packet,"CHATID");
	if (client_context->indexrow != -1){
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
				gdk_threads_add_idle(mx_create_message, pack);
			}
	}

}
