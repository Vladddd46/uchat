#include "client.h"


void draw_edit_profile(GtkWidget *widget, gpointer data){
    editwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable (GTK_WINDOW(editwindow), FALSE);
    gtk_window_set_transient_for (GTK_WINDOW(editwindow),GTK_WINDOW(window));
    gtk_window_set_title(GTK_WINDOW(editwindow),"Settings");
    gtk_widget_set_size_request(GTK_WIDGET(editwindow),300,500);

    editfixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(editwindow), editfixed);
    g_idle_add ((int (*)(void *))show_widget, editwindow);
}

void download_messages(GtkWidget *widget, gpointer data){
 
    // printf("%d\n",client_context->indexrow );
    // printf("%d\n",client_context->counter );

    cJSON *packet = cJSON_CreateObject();
    char  *packet_str = NULL;
    cJSON *type = cJSON_CreateString((char*)"msg_c");
    cJSON *chat_id = cJSON_CreateString((char*)mx_itoa(client_context->indexrow + 1));
    cJSON *from = cJSON_CreateString((char*)mx_itoa(client_context->counter));
    cJSON *to = cJSON_CreateString((char*)mx_itoa(client_context->counter + 15));
    cJSON *chat_name = cJSON_CreateString((char*)client_context -> username);
    cJSON *to_user = cJSON_CreateString((char*)client_context -> username);

    
    cJSON_AddItemToObject(packet, "TYPE", type);
    cJSON_AddItemToObject(packet, "CHATID", chat_id);
    cJSON_AddItemToObject(packet, "FROMMSG", from);
    cJSON_AddItemToObject(packet, "TOMSG", to);
    cJSON_AddItemToObject(packet, "CHATNAME", chat_name);
    cJSON_AddItemToObject(packet, "TO", to_user);
   // printf("type: %s\nchat_id: %s\nfrom: %s\nto: %s\nchat_name: %s\n\n", (char*)"msg_c", (char*)mx_itoa(client_context->indexrow + 1), (char*)mx_itoa(client_context->counter), (char*)mx_itoa(client_context->counter + 15), (char*)client_context -> username);

    packet_str = mx_string_copy(cJSON_Print(packet));
    char *packet_str1 =  packet_len_prefix_adder(packet_str);

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

 res = gtk_dialog_run (GTK_DIALOG (dialog));
 if (res == GTK_RESPONSE_OK)
   {
     char *filename;
     GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
     filename = gtk_file_chooser_get_filename (chooser);
     printf("%s\n",filename );
       g_free (filename);
   }

 gtk_widget_destroy (dialog);
 }


static bool release_button = FALSE;

gboolean my_keypress_function (GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (event->keyval == 65505 || event->keyval == 65507) {
        release_button = TRUE;
    }
    if (event->keyval == 65293 && release_button == FALSE){
        gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, create_message_system, NULL, 0);
    }
    return FALSE;
}

gboolean button_release (GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (event->keyval == 65505) {
        release_button = FALSE;
    }
    if (event->keyval == 65293 && release_button == FALSE)
    {
        gtk_text_buffer_set_text (GTK_TEXT_BUFFER(textbuffer),"",-1);
    }
    return FALSE;
}

gboolean draw_message_menu(void *data){
      t_s_glade *gui = (t_s_glade *)data;
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

    searchmenu = gtk_text_view_new ();
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
