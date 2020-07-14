#include "client.h"


void login_system(client_context_t *client_context, char *packet) {
	char *length = get_value_by_key(packet,"LENGTH");
	client_context->username = get_value_by_key(packet,"TO");
	int len = atoi(length);
	free(length);
	struct struct_type arg;
	arg.pack = packet;
	draw_message_menu(entryspawn, client_context);
	for (int i = 0; len > i; i++){
		//gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, create_row, NULL, 0);
		create_row(NULL, arg);
	}
}


