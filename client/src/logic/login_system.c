#include "client.h"


void login_system(client_context_t *client_context, char *packet) {
	char *length = get_value_by_key(packet,"LENGTH");
	client_context->username = get_value_by_key(packet,"TO");
	int len = atoi(length);
	free(length);
	struct struct_type arg;
	arg.pack = packet;
	gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, draw_message_menu, NULL, 0);
	int i = 0;
	while (len > i && !gtk_events_pending()){
		gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, create_row, mx_string_copy(packet), 0);
		//create_row(NULL, arg);
		i++;
	}
}


