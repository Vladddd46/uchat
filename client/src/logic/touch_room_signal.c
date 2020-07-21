#include "client.h"
//bool flagG = FALSE;


gboolean send_sticker(void *data){
    t_s_glade *pack = (t_s_glade *)data;  
  GtkAdjustment *adj;
  printf("%s\n",pack->pack );

    // char *nameuser = client_context->username;
    // char *sender = get_value_by_key(pack->pack,mx_strjoin("SENDER",mx_itoa(pack->number)));
    // int messagenum = atoi(get_value_by_key(pack->pack,mx_strjoin("ID",mx_itoa(pack->number))));
    // char *messagetext = get_value_by_key(pack->pack,mx_strjoin("MESSAGE",mx_itoa(pack->number)));
    // char *timemessage = get_value_by_key(pack->pack,mx_strjoin("TIME",mx_itoa(pack->number)));    // почисти память

    adj = gtk_adjustment_new(10000, 100000, -1000, 100, 10000, 10000);
    row = gtk_list_box_row_new();
    gtk_list_box_row_set_selectable (GTK_LIST_BOX_ROW(row),FALSE);
    gtk_list_box_insert (GTK_LIST_BOX(listboxmess),row,0);

    horizontalbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_container_add(GTK_CONTAINER(row), horizontalbox);

    // if (!strcmp(nameuser,sender))
    //     gtk_box_pack_end(GTK_BOX(horizontalbox),messagebox, FALSE, FALSE, 0);
    // else
    //     gtk_box_pack_start(GTK_BOX(horizontalbox),messagebox, FALSE, FALSE, 0);
    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/pokemon-2.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(iconn);
    gtk_box_pack_start(GTK_BOX(horizontalbox),icon, FALSE, FALSE, 0);

    // labellmenu = gtk_label_new(sender);
    // gtk_widget_set_name(labellmenu,"labellmenu");
    // gtk_box_pack_start(GTK_BOX(verticalbox),labellmenu, FALSE, FALSE, 0);
    iconn = gdk_pixbuf_new_from_file(pack->pack,NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
    stickermessage = gtk_image_new_from_pixbuf(iconn);
    gtk_box_pack_start(GTK_BOX(horizontalbox),stickermessage, FALSE, FALSE, 0);

    // labellmenu3 = gtk_label_new(timemessage);
    // gtk_box_pack_start(GTK_BOX(messagebox),labellmenu3, FALSE, FALSE, 0);

 
 //menu with edit and delete button
    // fileMenu = gtk_menu_new();
    // g_signal_connect_swapped(G_OBJECT(ebox), "button-press-event", G_CALLBACK(show_popup), fileMenu);

    // edit = gtk_menu_item_new_with_label("Edit");
    // g_idle_add ((int (*)(void *))show_widget, edit);
    // gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), edit);
    // g_signal_connect (edit, "activate", G_CALLBACK (edit_message), labellmenu2);

    // delet = gtk_menu_item_new_with_label("Delete");
    // g_idle_add ((int (*)(void *))show_widget, delet);
    // gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu), delet);  
    // g_signal_connect (delet, "activate", G_CALLBACK (delete_message), row);

    
    g_idle_add ((int (*)(void *))show_widget, window);
    //gtk_widget_show_all(window);
    gtk_scrolled_window_set_vadjustment(GTK_SCROLLED_WINDOW(scrollmess), adj);
    client_context->counter+=1;
    pack->number+=1;
    return 0;
}








void sticker_send_system(GtkWidget* widget, gpointer data){
    char *path = g_object_get_data(G_OBJECT(widget),"sticker path");
    char  *packet_str = NULL;
    char *all_users = client_context->allusers;
    cJSON *packet = cJSON_CreateObject();
    cJSON *type   = cJSON_CreateString("add_msg_c");
    cJSON *type2  = cJSON_CreateString("sticker");
    char *current_time = mx_get_time();
    if (current_time == NULL)
         mx_null_error("150: current_time is NULL");
    cJSON *time        = cJSON_CreateString(current_time);
    cJSON *msg         = cJSON_CreateString(path);
    cJSON *allusers    = cJSON_CreateString(all_users);
    cJSON *message_id  = cJSON_CreateString("0");
    int chat_id_client = client_context->indexrow;
    cJSON *chat_id     = cJSON_CreateString(client_context->mas[client_context->indexrow]);
    cJSON *username    = cJSON_CreateString(client_context -> username);
    
    cJSON_AddItemToObject(packet, "TYPE", type);
    cJSON_AddItemToObject(packet, "TYPE2", type2);
    cJSON_AddItemToObject(packet, "MESSAGEID", message_id);
    cJSON_AddItemToObject(packet, "TIME", time);
    cJSON_AddItemToObject(packet, "TO", allusers);
    cJSON_AddItemToObject(packet, "MESSAGE", msg);
    cJSON_AddItemToObject(packet, "CHATID", chat_id);
    cJSON_AddItemToObject(packet, "SENDER", username);

    packet_str = mx_string_copy(cJSON_Print(packet));

    char *packet_str1 =  packet_len_prefix_adder(packet_str);
    printf("[outcomming packet]%s\n", packet_str1);
    send(client_context->sockfd, packet_str1, (int)strlen(packet_str1), 0);
    free(packet_str);
    free(packet_str1);
    // t_s_glade *gui = (t_s_glade *)malloc(sizeof(t_s_glade));
    // gui->pack = mx_strdup(path);
    // gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, send_sticker, gui, 0);
}

void sticker_menu(GtkWidget* widget, gpointer data){
    stickerwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_name(stickerwindow,"stickerwindow");
    gtk_window_set_resizable (GTK_WINDOW(stickerwindow), FALSE);
    gtk_window_set_transient_for (GTK_WINDOW(stickerwindow),GTK_WINDOW(window));
    gtk_window_set_title(GTK_WINDOW(stickerwindow),"Stickers menu");
    gtk_widget_set_size_request(GTK_WIDGET(stickerwindow),400,300);

    stickerfixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(stickerwindow),stickerfixed);

    stickerebox = gtk_event_box_new();
    gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,0,0);
    g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/1.png ");
    g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(sticker_send_system),NULL);


    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/1.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
    stickerimage = gtk_image_new_from_pixbuf(iconn);
    gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

    stickerebox = gtk_event_box_new();
    gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,100,0);
    g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/2.png ");
    g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(sticker_send_system),NULL);

    iconn = gdk_pixbuf_new_from_file("./media/img/2.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
    stickerimage = gtk_image_new_from_pixbuf(iconn);
    gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

    stickerebox = gtk_event_box_new();
    gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,200,0);
    g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/3.png ");
    g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(sticker_send_system),NULL);

    iconn = gdk_pixbuf_new_from_file("./media/img/3.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
    stickerimage = gtk_image_new_from_pixbuf(iconn);
    gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

    stickerebox = gtk_event_box_new();
    gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,300,0);
    g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/4.png ");
    g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(sticker_send_system),NULL);

    iconn = gdk_pixbuf_new_from_file("./media/img/4.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
    stickerimage = gtk_image_new_from_pixbuf(iconn);
    gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

     stickerebox = gtk_event_box_new();
    gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,0,100);
    g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/5.png ");
    g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(sticker_send_system),NULL);

    iconn = gdk_pixbuf_new_from_file("./media/img/5.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
    stickerimage = gtk_image_new_from_pixbuf(iconn);
    gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

     stickerebox = gtk_event_box_new();
    gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,100,100);
    g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/6.png ");
    g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(sticker_send_system),NULL);

    iconn = gdk_pixbuf_new_from_file("./media/img/6.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
    stickerimage = gtk_image_new_from_pixbuf(iconn);
    gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

     stickerebox = gtk_event_box_new();
    gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,200,100);
    g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/7.png ");
    g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(sticker_send_system),NULL);

    iconn = gdk_pixbuf_new_from_file("./media/img/7.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
    stickerimage = gtk_image_new_from_pixbuf(iconn);
    gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

     stickerebox = gtk_event_box_new();
    gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,300,100);
    g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/8.png ");
    g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(sticker_send_system),NULL);

    iconn = gdk_pixbuf_new_from_file("./media/img/8.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
    stickerimage = gtk_image_new_from_pixbuf(iconn);
    gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

     stickerebox = gtk_event_box_new();
    gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,0,200);
    g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/9.png ");
    g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(sticker_send_system),NULL);

    iconn = gdk_pixbuf_new_from_file("./media/img/9.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
    stickerimage = gtk_image_new_from_pixbuf(iconn);
    gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

    stickerebox = gtk_event_box_new();
    gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,100,200);
    g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/10.png ");
    g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(sticker_send_system),NULL);

    iconn = gdk_pixbuf_new_from_file("./media/img/10.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
    stickerimage = gtk_image_new_from_pixbuf(iconn);
    gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

     stickerebox = gtk_event_box_new();
    gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,200,200);
    g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/11.png ");
    g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(sticker_send_system),NULL);

    iconn = gdk_pixbuf_new_from_file("./media/img/11.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
    stickerimage = gtk_image_new_from_pixbuf(iconn);
    gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

     stickerebox = gtk_event_box_new();
    gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,300,200);
    g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/12.png ");
    g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(sticker_send_system),NULL);

    iconn = gdk_pixbuf_new_from_file("./media/img/12.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
    stickerimage = gtk_image_new_from_pixbuf(iconn);
    gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

      g_idle_add ((int (*)(void *))show_widget, stickerwindow);
}

void touch_room_signal(GtkWidget *listbox, void *socket){
    client_context->counter = 0;
    GtkListBoxRow *selectedrow = gtk_list_box_get_selected_row(GTK_LIST_BOX(listbox));
    int indexrow = gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(selectedrow));
    printf("%d\n",indexrow );
    client_context->indexrow =indexrow;
    GList *gl = gtk_container_get_children(GTK_CONTAINER(selectedrow));
    GtkGrid *gridchild = gl->data;
    GtkWidget *lab = gtk_grid_get_child_at(gridchild,1,0);
    //printf("%s\n","touch_room_signal" );

    if( client_context->flag == FALSE){
        scrollnewmess = gtk_scrolled_window_new(0,0);
         gtk_fixed_put(GTK_FIXED (fixed), scrollnewmess, 300,718);
         gtk_widget_set_size_request(scrollnewmess,724,50);

        downbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0); 
        gtk_widget_set_size_request(downbox,724,50);
        gtk_widget_set_name(downbox,"downbox");
        gtk_container_add(GTK_CONTAINER(scrollnewmess), downbox);

        buttonrefresh = gtk_button_new_with_label("download old messages"); 
        gtk_box_pack_start(GTK_BOX(rightbox),buttonrefresh,FALSE,FALSE,0);
        g_signal_connect(buttonrefresh,"clicked", G_CALLBACK(download_messages), NULL);

        screp = gtk_button_new();
        gtk_box_pack_start(GTK_BOX(downbox), screp, FALSE, FALSE, 0);
        GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/screp.png",NULL); 
        iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
        icon = gtk_image_new_from_pixbuf(iconn);
        gtk_button_set_image (GTK_BUTTON (screp), icon);
        g_signal_connect(screp, "clicked", G_CALLBACK(dialog), NULL);


        sticker = gtk_button_new();
        gtk_box_pack_start(GTK_BOX(downbox), sticker, FALSE, FALSE, 0);
        iconn = gdk_pixbuf_new_from_file("./media/img/sticker.png",NULL); 
        iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
        icon = gtk_image_new_from_pixbuf(iconn);
        gtk_button_set_image (GTK_BUTTON (sticker), icon);
        g_signal_connect(sticker, "clicked", G_CALLBACK(sticker_menu), NULL);

        textbuffer = gtk_text_buffer_new(NULL);
        newmessedgentry = gtk_text_view_new_with_buffer(textbuffer);
        gtk_widget_set_name(newmessedgentry,"newmessedgentry");
        gtk_box_pack_start(GTK_BOX(downbox),newmessedgentry, TRUE, TRUE, 0);
        g_signal_connect (G_OBJECT (newmessedgentry), "key_release_event", G_CALLBACK (button_release), NULL);
        g_signal_connect (G_OBJECT (newmessedgentry), "key_press_event", G_CALLBACK (my_keypress_function), NULL);
        
        scrollmess = gtk_scrolled_window_new(0,0);
        gtk_fixed_put(GTK_FIXED (fixed), scrollmess, 300,50);
        gtk_widget_set_name(scrollmess,"scrollmess");
        gtk_widget_set_size_request(GTK_WIDGET(scrollmess),724,668);
        ///////////////////// g_signal_connect(scrollmess,"edge_reached",G_CALLBACK(download_messages), pos);

        listboxmess = gtk_list_box_new();
        gtk_widget_set_name(listboxmess,"listboxmess");
        gtk_container_add(GTK_CONTAINER(scrollmess), listboxmess);
         g_idle_add ((int (*)(void *))show_widget, window);
        client_context->flag = TRUE;
    }
   
    int *test = (int *)socket;
    char *chat_name = client_context->username;
    char chat_id[40];
    bzero(chat_id, 40);
    chat_name = mx_strjoin("CHATNAME:", chat_name);
    sprintf(chat_id, "CHATID:%d", ++indexrow);
    char* chat_id_str = mx_strjoin("CHATIDFROMDB:", client_context->mas[client_context->indexrow]);

    char *packet = json_packet_former(6, "TYPE:msg_c", chat_name, chat_id, "FROMMSG:0", "TOMSG:15", chat_id_str);
    packet = packet_len_prefix_adder(packet);
    printf("PACKet berfore send %s\n\n", packet);

    printf("%d\n", client_context->sockfd);
    
    send(client_context->sockfd, packet, mx_strlen(packet), 0);
     printf("%s\n","packet sended" );
}
