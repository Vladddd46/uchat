#include "client.h"

gboolean mx_draw_list_box_system(void *data){
    char *packet = (char *)data;
    char *len_str = get_value_by_key(packet,"LENGTH");
	int len = atoi(len_str);
	gtk_widget_destroy(miniscroll);
	miniscroll = gtk_scrolled_window_new(0,0);
    gtk_fixed_put(GTK_FIXED (minifixed), miniscroll, 25,100);
    gtk_widget_set_size_request(GTK_WIDGET(miniscroll),250,350);
    minilistbox = gtk_list_box_new();
    gtk_container_add(GTK_CONTAINER(miniscroll), minilistbox);
	for (int i = 0; i < len; i++){
        char *nicknamex = mx_strjoin("NICKNAME",mx_itoa(i));
		char *nickname = get_value_by_key(packet, nicknamex);
        char *loginx = mx_strjoin("LOGIN",mx_itoa(i));
		char *login = get_value_by_key(packet, loginx);
        t_s_glade *pack = (t_s_glade *)malloc(sizeof(t_s_glade));
        pack->number = i;
        pack->login = login;
        pack->login = mx_string_copy(pack->login);
        pack->nickname = nickname;
        pack->nickname = mx_string_copy(pack->nickname);
		gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, mx_draw_list_box, pack, 0);
	}
    return 0;
}
