#include "client.h"

gboolean add_new_friend(GtkWidget *widget, gpointer data) {
   char  *login = g_object_get_data(G_OBJECT(widget),"name user");
   printf("%s\n",login );

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
    if (packet_str1 == NULL)
        mx_null_error("27: add_new_friend");
    printf(">>>>>>>>>>>>>%s\n",packet_str1 );
    send(client_context->sockfd, mx_strdup(packet_str1), (int)strlen(packet_str1), 0);
    free(packet_str);
    free(packet_str1);
    return FALSE;
}

gboolean draw_list_box_system(void *data){
    char *packet = (char *)data;
    char *len_str = get_value_by_key(packet,"LENGTH");
    if (len_str == NULL)
        mx_null_error("38: draw_list_box_system");
	int len = atoi(len_str);
    free(len_str);

	gtk_widget_destroy(miniscroll);
	miniscroll = gtk_scrolled_window_new(0,0);
    gtk_fixed_put(GTK_FIXED (minifixed), miniscroll, 25,100);
    gtk_widget_set_size_request(GTK_WIDGET(miniscroll),250,350);

    minilistbox = gtk_list_box_new();
    gtk_container_add(GTK_CONTAINER(miniscroll), minilistbox);

	for(int i = 0; i < len; i++){

        char *nicknamex = mx_strjoin("NICKNAME",mx_itoa(i));
        if (nicknamex == NULL)
            mx_null_error("54: draw_list_box_system");
		char *nickname = get_value_by_key(packet, nicknamex);
         if (nickname == NULL)
            mx_null_error("57: draw_list_box_system");

        char *loginx = mx_strjoin("LOGIN",mx_itoa(i));
        if (loginx == NULL)
            mx_null_error("61: draw_list_box_system");
		char *login = get_value_by_key(packet, loginx);
        if (login == NULL)
            mx_null_error("66: draw_list_box_system");


        t_s_glade *pack = (t_s_glade *)malloc(sizeof(t_s_glade));
        if (pack == NULL)
            mx_null_error("55: draw_list_box_system");
        pack->number = i;
        pack->login = login;
        pack->login = mx_string_copy(pack->login);
        pack->nickname = nickname;
        pack->nickname = mx_string_copy(pack->nickname);
		gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, draw_list_box, pack, 0);
	}
    return 0;

}
 
gboolean draw_list_box(void *data){
	t_s_glade *pack = (t_s_glade *)data; 
    minirow = gtk_list_box_row_new();
	gtk_list_box_insert (GTK_LIST_BOX(minilistbox), minirow, pack->number);

	minibox = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(minirow), minibox);

	minilabell = gtk_label_new(pack->login);
	gtk_grid_attach(GTK_GRID(minibox),minilabell, 0, 0, 1, 1);

	minilabell2 = gtk_label_new(pack->nickname);
	gtk_grid_attach(GTK_GRID(minibox),minilabell2, 0, 1, 1, 1); 

    minieventbox = gtk_event_box_new();
    g_object_set_data(G_OBJECT(minieventbox),"name user",pack->login);
    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/plus_icon.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(iconn);
    gtk_grid_attach(GTK_GRID(minibox),minieventbox, 1, 0, 2, 2);
    gtk_container_add(GTK_CONTAINER(minieventbox), icon);
    g_signal_connect(minieventbox,"button-release-event", G_CALLBACK(add_new_friend), minilistbox);
    gtk_list_box_select_row(GTK_LIST_BOX(minilistbox),GTK_LIST_BOX_ROW(minirow));

	g_idle_add ((int (*)(void *))show_widget, miniwindow);
    return 0;
}

gboolean mini_button_release (GtkWidget *widget, GdkEventKey *event, gpointer data) {
  	char *editbuff = (char *)gtk_entry_get_text(GTK_ENTRY(minientry));
  	cJSON *packet = cJSON_CreateObject();
    char  *packet_str = NULL;
  	cJSON *type = cJSON_CreateString("find_user_c");
    cJSON *user = cJSON_CreateString(editbuff);
    cJSON *nick = cJSON_CreateString(client_context->username);

    cJSON_AddItemToObject(packet, "TYPE", type);
    cJSON_AddItemToObject(packet, "USER", user);
    cJSON_AddItemToObject(packet, "TO", nick);
    packet_str = mx_string_copy(cJSON_Print(packet));
    packet_str =  packet_len_prefix_adder(packet_str);
    if (packet_str == NULL)
        mx_null_error("123: draw_list_box_system");
    send(client_context->sockfd, packet_str, (int)strlen(packet_str), 0);
    return FALSE;
}

void add_new_user(GtkWidget *newchatbutton, gpointer data){
	miniwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable (GTK_WINDOW(miniwindow), FALSE);
    gtk_window_set_transient_for (GTK_WINDOW(miniwindow),GTK_WINDOW(window));
    if (client_context->Ukraine == FALSE)
        gtk_window_set_title(GTK_WINDOW(miniwindow),"Find User");
    else
        buttonrefresh = gtk_button_new_with_label("Знайти Користувача"); 
    gtk_widget_set_size_request(GTK_WIDGET(miniwindow),300,500);

    minifixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(miniwindow), minifixed);

    minientry = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED (minifixed), minientry, 50,50);
    gtk_widget_set_size_request(GTK_WIDGET(minientry),200,40);

    if (client_context->Ukraine == FALSE)
        minibuttonfind = gtk_button_new_with_label("Find User");
    else
        minibuttonfind = gtk_button_new_with_label("Знайти Користувача");
    gtk_widget_set_name(minibuttonfind,"minibuttonfind");
    gtk_fixed_put(GTK_FIXED (minifixed), minibuttonfind, 90,10);
    g_signal_connect (G_OBJECT (minibuttonfind), "clicked", G_CALLBACK (mini_button_release), NULL);

    miniscroll = gtk_scrolled_window_new(0,0);
    gtk_fixed_put(GTK_FIXED (minifixed), miniscroll, 25,100);
    gtk_widget_set_size_request(GTK_WIDGET(miniscroll),250,350);

    minilistbox = gtk_list_box_new();
    gtk_container_add(GTK_CONTAINER(miniscroll), minilistbox);
    gtk_widget_set_name(minilistbox,"minilistbox");

    g_idle_add ((int (*)(void *))show_widget, miniwindow);

}
