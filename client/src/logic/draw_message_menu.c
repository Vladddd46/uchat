#include "client.h"
        

void switchlanguage_system(GtkSwitch *widget,
               gboolean   state,
               gpointer   user_data){
    if (state == TRUE){
        printf("%s\n","UKraine" );
        system("open ./media/gimn.mp3");
        client_context->Ukraine = TRUE;
    }
    if (state == FALSE) {
        client_context->Ukraine = FALSE;
        printf("%s\n","English" ); 
    }
}        

void logout_system(GtkWidget *widget, gpointer data){
    close_window(editwindow);
    gtk_widget_destroy(fixed);
    g_idle_add ((int (*)(void *))show_widget, window);
    fixed = gtk_fixed_new();
    char *packet = json_packet_former(1, "TYPE:logout_c");
    packet = packet_len_prefix_adder(packet);
    send(client_context->sockfd, packet, mx_strlen(packet), 0);
    printf(">>>>%s\n",packet );
    gtk_container_add(GTK_CONTAINER(window), fixed);
    main_menu();

}

void change_password_system(GtkWidget* widget, gpointer data){
    char *password = (char *)gtk_entry_get_text(GTK_ENTRY(widget));
    password = mx_strjoin("TO:",password);
    char *login = mx_strjoin("LOGIN:",client_context->username);
    char *packet = json_packet_former(3, "TYPE:change_password_c", login, password);
    packet = packet_len_prefix_adder(packet);
    send(client_context->sockfd, packet, mx_strlen(packet), 0);
    close_window(editwindow);

}



void draw_edit_profile(GtkWidget *widget, gpointer data){
    editwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable (GTK_WINDOW(editwindow), FALSE);
    gtk_window_set_transient_for (GTK_WINDOW(editwindow),GTK_WINDOW(window));
    if (client_context->Ukraine == FALSE)
        gtk_window_set_title(GTK_WINDOW(editwindow),"Settings");
    else
        gtk_window_set_title(GTK_WINDOW(editwindow),"Налаштування");
    gtk_widget_set_size_request(GTK_WIDGET(editwindow),300,500);

    editfixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(editwindow), editfixed);

    editgrid = gtk_grid_new();
    gtk_fixed_put(GTK_FIXED(editfixed),editgrid,25,100);
    //gtk_widget_set_size_request(editgrid, 180, 300);
    gtk_widget_set_name(editgrid,"editgrid");
    if (client_context->Ukraine == FALSE)
        themelabel = gtk_label_new("Dark mode");
    else
        themelabel = gtk_label_new("Темна тема");
    gtk_grid_attach(GTK_GRID(editgrid),themelabel, 0, 0, 1, 1);

    switchtheme = gtk_switch_new();
    gtk_grid_attach(GTK_GRID(editgrid),switchtheme, 0, 1, 1, 1);
    gtk_widget_set_size_request(switchtheme,25,25);
     if (client_context->Ukraine == FALSE)
        languagelabel = gtk_label_new("Ukrainan");
    else
        languagelabel = gtk_label_new("Українська");
    gtk_grid_attach(GTK_GRID(editgrid),languagelabel, 0, 2, 1, 1);
    
    switchlanguage = gtk_switch_new();
    if(client_context->Ukraine == TRUE)
        gtk_switch_set_state(GTK_SWITCH(switchlanguage),TRUE);
    gtk_grid_attach(GTK_GRID(editgrid),switchlanguage, 0, 3, 1, 1);
    g_signal_connect(switchlanguage,"state-set", G_CALLBACK(switchlanguage_system), NULL);

    changepassword = gtk_entry_new();
    if (client_context->Ukraine == FALSE)
        gtk_entry_set_placeholder_text(GTK_ENTRY(changepassword),"Change password");
    else
        gtk_entry_set_placeholder_text(GTK_ENTRY(changepassword),"Змінити пароль");
    gtk_grid_attach(GTK_GRID(editgrid),changepassword, 0, 4, 2, 1);
    g_signal_connect(changepassword,"activate", G_CALLBACK(change_password_system), NULL);

     if (client_context->Ukraine == FALSE)
        logout = gtk_button_new_with_label("logout");
    else
        logout = gtk_button_new_with_label("Вихід");
     gtk_grid_attach(GTK_GRID(editgrid),logout, 0, 5, 1, 1);
    g_signal_connect(logout,"clicked", G_CALLBACK(logout_system), NULL);


    g_idle_add ((int (*)(void *))show_widget, editwindow);
}

void download_messages(GtkWidget *widget, gpointer data){
  
    cJSON *packet = cJSON_CreateObject();
    char  *packet_str = NULL;
    cJSON *type = cJSON_CreateString((char*)"msg_c");

    char *chat_id_str = (char*)mx_itoa(client_context->indexrow + 1);
    if (chat_id_str == NULL)
        mx_null_error("26: download_messages");
    cJSON *chat_id = cJSON_CreateString(chat_id_str);
    free(chat_id_str);

    char *from_str = (char*)mx_itoa(client_context->counter);
    if (from_str == NULL)
        mx_null_error("31: download_messages");
    cJSON *from = cJSON_CreateString(from_str);

    char *to_str = (char*)mx_itoa(client_context->counter + 15);
    if (to_str == NULL)
        mx_null_error("36: download_messages");
    cJSON *to = cJSON_CreateString(to_str);

    char *chat_name_str = (char *)client_context -> username;
    if (chat_name_str == NULL)
        mx_null_error("41: download_messages");
    cJSON *chat_name = cJSON_CreateString(chat_name_str);


    char *to_user_str = (char*)client_context -> username;
    if (to_user_str == NULL)
        mx_null_error("46: download_messages");
    cJSON *to_user = cJSON_CreateString(to_user_str);


    char *chat_id_sql_str = (char*)client_context->mas[client_context->indexrow];
    if (chat_id_sql_str == NULL)
        mx_null_error("52: download_messages");
    cJSON *chat_id_sql = cJSON_CreateString(chat_id_sql_str);
    
    cJSON_AddItemToObject(packet, "TYPE", type);
    cJSON_AddItemToObject(packet, "CHATID", chat_id);
    cJSON_AddItemToObject(packet, "FROMMSG", from);
    cJSON_AddItemToObject(packet, "TOMSG", to);
    cJSON_AddItemToObject(packet, "CHATNAME", chat_name);
    cJSON_AddItemToObject(packet, "TO", to_user);
    cJSON_AddItemToObject(packet, "CHATIDFROMDB:", chat_id_sql);

    packet_str         = mx_string_copy(cJSON_Print(packet));
    char *packet_str1 =  packet_len_prefix_adder(packet_str);
    if (packet_str1 == NULL)
        mx_null_error("66: download_messages");

    send(client_context->sockfd, mx_strdup(packet_str1), (int)strlen(packet_str1), 0);
    free(packet_str);
    free(packet_str1);
}

void dialog(GtkWidget *widget, gpointer data ){
 GtkWidget *dialog;
 GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
 gint res;   

 dialog = gtk_file_chooser_dialog_new ("Open File",
                                       GTK_WINDOW(window),
                                       action,
                                       ("_Cancel"),
                                       GTK_RESPONSE_CANCEL,
                                       ("_Open"),
                                       GTK_RESPONSE_OK,
                                       NULL);

 res = gtk_dialog_run(GTK_DIALOG(dialog));
 if (res == GTK_RESPONSE_OK) {
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
    filename = gtk_file_chooser_get_filename (chooser);
    g_free(filename);
 }

    gtk_widget_destroy (dialog);
}


static bool release_button = FALSE;

gboolean my_keypress_function (GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (event->keyval == 65505 || event->keyval == 65507)
        release_button = TRUE;
    if (event->keyval == 65293 && release_button == FALSE)
        gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, create_message_system, NULL, 0); 
    return FALSE;
}

gboolean button_release (GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (event->keyval == 65505)
        release_button = FALSE;
    if (event->keyval == 65293 && release_button == FALSE)
        gtk_text_buffer_set_text (GTK_TEXT_BUFFER(textbuffer),"",-1);
    return FALSE;
}

gboolean draw_message_menu(void *data){
    t_s_glade *gui = (t_s_glade *)data;
    client_context->flag = FALSE;
    GtkPositionType *pos = NULL;
    //отрисовка основного меню с чатами и комнатами
    gtk_widget_destroy(fixed);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed); 

    scroll = gtk_scrolled_window_new(0,0);
    gtk_fixed_put(GTK_FIXED (fixed), scroll, 0,50);

    leftbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_widget_set_size_request(leftbox,300,50);
    gtk_widget_set_name(leftbox,"leftbox");
    gtk_fixed_put(GTK_FIXED (fixed), leftbox, 0,0);

    leftmenu = gtk_button_new();
    gtk_box_pack_start(GTK_BOX(leftbox), leftmenu, TRUE, TRUE, 0);
    gtk_widget_set_name(leftmenu,"leftmenu");
    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/menu_icon.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(iconn);
    gtk_button_set_image (GTK_BUTTON (leftmenu), icon);
    g_signal_connect(leftmenu,"clicked", G_CALLBACK(draw_edit_profile), NULL);

    searchmenu = gtk_text_view_new();
    gtk_widget_set_size_request(searchmenu,150,50);
    gtk_widget_set_name(searchmenu,"searchmenu");
    gtk_box_pack_start(GTK_BOX(leftbox),searchmenu, TRUE, TRUE, 10);
    

    newchatbutton = gtk_button_new();
    gtk_box_pack_end(GTK_BOX(leftbox), newchatbutton, TRUE, TRUE, 0);
    iconn = gdk_pixbuf_new_from_file("./media/img/plus_icon.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(iconn);
    gtk_button_set_image (GTK_BUTTON (newchatbutton), icon);
    g_signal_connect(newchatbutton,"clicked", G_CALLBACK(add_new_user), NULL);

    rightbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_widget_set_size_request(rightbox,724,50);
    gtk_widget_set_name(rightbox,"rightbox");
    gtk_fixed_put(GTK_FIXED (fixed), rightbox, 300,0);

  

    listbox = gtk_list_box_new();
    gtk_widget_set_name(listbox,"listboxleft");
    gtk_widget_set_size_request(scroll,300,718);
    gtk_container_add(GTK_CONTAINER(scroll), listbox);

    g_signal_connect(listbox,"row-activated", G_CALLBACK(touch_room_signal), &client_context->sockfd);
    g_idle_add ((int (*)(void *))show_widget, window);
    return 0;
}
