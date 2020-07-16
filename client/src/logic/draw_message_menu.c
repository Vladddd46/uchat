#include "client.h"

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

     scrollnewmess = gtk_scrolled_window_new(0,0);
     gtk_fixed_put(GTK_FIXED (fixed), scrollnewmess, 300,718);
     gtk_widget_set_size_request(scrollnewmess,724,50);

    downbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_widget_set_size_request(downbox,724,50);
    gtk_widget_set_name(downbox,"downbox");
    gtk_container_add(GTK_CONTAINER(scrollnewmess), downbox);

    screp = gtk_button_new();
    gtk_box_pack_start(GTK_BOX(downbox), screp, FALSE, FALSE, 0);
    iconn = gdk_pixbuf_new_from_file("./media/img/screp.png",NULL); 
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

    listboxmess = gtk_list_box_new();
    gtk_widget_set_name(listboxmess,"listboxmess");
    gtk_container_add(GTK_CONTAINER(scrollmess), listboxmess);

     g_idle_add ((int (*)(void *))show_widget, window);
     return 0;
}
