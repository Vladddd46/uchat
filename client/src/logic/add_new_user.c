#include "client.h"

// gboolean mini_my_keypress_function (GtkWidget *widget, GdkEventKey *event, gpointer data) {
//     if (event->keyval == 65505 || event->keyval == 65507) {
//         release_button = TRUE;
//     }
//     if (event->keyval == 65293 && release_button == FALSE){
//         //create_message_client(newmessedgentry, NULL);
//     }
//     return FALSE;
// }
gboolean add_new_friend (GtkWidget *newchatbutton, gpointer data) {
	
	GtkListBoxRow *selectedrow= gtk_list_box_get_selected_row(GTK_LIST_BOX(minilistbox));
	GList *gl = gtk_container_get_children(GTK_CONTAINER(selectedrow));
    GtkGrid *widgetchild = gl->data;
 	GtkWidget *minilogin = gtk_grid_get_child_at(GTK_GRID(minibox),0,0);
 	char *login = (char *)gtk_label_get_text(GTK_LABEL(minilogin));
   	// printf("%s\n",client_context->username);
   	// printf("%s\n",login );

  	cJSON *packet = cJSON_CreateObject();
    char  *packet_str = NULL;
  	cJSON *type = cJSON_CreateString("add_contact_c");
    cJSON *user = cJSON_CreateString(login);
    cJSON *nick = cJSON_CreateString(client_context->username);

    cJSON_AddItemToObject(packet, "TYPE", type);
    cJSON_AddItemToObject(packet, "USER", user);
    cJSON_AddItemToObject(packet, "TO", nick);
    packet_str = mx_string_copy(cJSON_Print(packet));
    char *packet_str1 =  packet_len_prefix_adder(packet_str);
   // printf("%s\n",packet_str );
    send(client_context->sockfd, packet_str, (int)strlen(packet_str), 0);
    free(packet_str);
    free(packet_str1);
    return FALSE;
}

void draw_list_box_system(char *packet){
	int len = atoi(get_value_by_key(packet,"LENGTH"));

    printf("====>%s\n", packet);
	gtk_widget_destroy(miniscroll);
	miniscroll = gtk_scrolled_window_new(0,0);
    gtk_fixed_put(GTK_FIXED (minifixed), miniscroll, 25,100);
    gtk_widget_set_size_request(GTK_WIDGET(miniscroll),250,350);

    minilistbox = gtk_list_box_new();
    gtk_container_add(GTK_CONTAINER(miniscroll), minilistbox);

	for(int i = 0; i < len; i++){
		char *nickname = (get_value_by_key(packet,mx_strjoin("NICKNAME",mx_itoa(i))));
		char *login = (get_value_by_key(packet,mx_strjoin("LOGIN",mx_itoa(i))));
		draw_list_box(login,nickname,i);
	}

}

void draw_list_box(char *login, char *nickname, int number){
	
    minirow = gtk_list_box_row_new();
	gtk_list_box_insert (GTK_LIST_BOX(minilistbox), minirow, number);

	minibox = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(minirow), minibox);

	minilabell = gtk_label_new(login);
	gtk_grid_attach(GTK_GRID(minibox),minilabell, 0, 0, 1, 1);

	minilabell2 = gtk_label_new(nickname);
	gtk_grid_attach(GTK_GRID(minibox),minilabell2, 0, 1, 1, 1);

    minieventbox = gtk_event_box_new();
    gtk_widget_set_name(minieventbox,"minieventbox");
    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/plus_icon.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(iconn);
    gtk_grid_attach(GTK_GRID(minibox),minieventbox, 1, 0, 2, 2);
    gtk_container_add(GTK_CONTAINER(minieventbox), icon);
    g_signal_connect(minieventbox,"button-release-event", G_CALLBACK(add_new_friend), NULL);

    gtk_list_box_select_row(GTK_LIST_BOX(minilistbox),GTK_LIST_BOX_ROW(minirow));

	gtk_widget_show_all(miniwindow);
}

gboolean mini_button_release (GtkWidget *widget, GdkEventKey *event, gpointer data) {
  	char *editbuff = (char *)gtk_entry_get_text(GTK_ENTRY(widget));
  	draw_list_box("Vlad","Vdepeshko",1);

  	cJSON *packet = cJSON_CreateObject();
    char  *packet_str = NULL;
  	cJSON *type = cJSON_CreateString("find_user_c");
    cJSON *user = cJSON_CreateString(editbuff);
    cJSON *nick = cJSON_CreateString("Yura");

    cJSON_AddItemToObject(packet, "TYPE", type);
    cJSON_AddItemToObject(packet, "USER", user);
    cJSON_AddItemToObject(packet, "TO", nick);
    packet_str = mx_string_copy(cJSON_Print(packet));
    packet_str =  packet_len_prefix_adder(packet_str);
    send(client_context->sockfd, packet_str, (int)strlen(packet_str), 0);
    return FALSE;
}

void add_new_user(GtkWidget *newchatbutton, gpointer data){
	miniwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable (GTK_WINDOW(miniwindow), FALSE);
    gtk_window_set_transient_for (GTK_WINDOW(miniwindow),GTK_WINDOW(window));
    gtk_widget_set_size_request(GTK_WIDGET(miniwindow),300,500);

    minifixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(miniwindow), minifixed);

    minientry = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED (minifixed), minientry, 50,50);
    gtk_widget_set_size_request(GTK_WIDGET(minientry),200,40);
    g_signal_connect (G_OBJECT (minientry), "key_release_event", G_CALLBACK (mini_button_release), NULL);
   // g_signal_connect (G_OBJECT (minientry), "key_press_event", G_CALLBACK (mini_my_keypress_function), NULL);

    miniscroll = gtk_scrolled_window_new(0,0);
    gtk_fixed_put(GTK_FIXED (minifixed), miniscroll, 25,100);
    gtk_widget_set_size_request(GTK_WIDGET(miniscroll),250,350);

    minilistbox = gtk_list_box_new();
    gtk_container_add(GTK_CONTAINER(miniscroll), minilistbox);
    gtk_widget_set_name(minilistbox,"minilistbox");
    

    gtk_widget_show_all(miniwindow);

}
