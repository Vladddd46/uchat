#include "client.h"
//bool flagG = FALSE;
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
