#include "client.h"

static bool release_button = FALSE;

gboolean my_keypress_function (GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (event->keyval == 65505 || event->keyval == 65507) {
        release_button = TRUE;
    }
    if (event->keyval == 65293 && release_button == FALSE){
            create_message(newmessedgentry, NULL);
            gtk_text_buffer_set_text (GTK_TEXT_BUFFER(textbuffer),"",-1);
        }
    return FALSE;
}

gboolean button_release (GtkWidget *widget, GdkEventKey *event, gpointer data) {
    if (event->keyval == 65505) {
        release_button = FALSE;
    }
    return FALSE;
}

void draw_message_menu(GtkWidget *entryspawn, client_context_t *client_context){
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
    g_signal_connect(newchatbutton, "clicked", G_CALLBACK(create_row), NULL);
    iconn = gdk_pixbuf_new_from_file("./media/img/plus_icon.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(iconn);
    gtk_button_set_image (GTK_BUTTON (newchatbutton), icon);

    rightbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_widget_set_size_request(rightbox,724,50);
    gtk_widget_set_name(rightbox,"rightbox");
    gtk_fixed_put(GTK_FIXED (fixed), rightbox, 300,0);

    listbox = gtk_list_box_new();
    gtk_widget_set_name(listbox,"listboxleft");
    gtk_widget_set_size_request(scroll,300,718);
    gtk_container_add(GTK_CONTAINER(scroll), listbox);

    scrollnewmess = gtk_scrolled_window_new(0,0);
    gtk_fixed_put(GTK_FIXED (fixed), scrollnewmess, 300,718);
    gtk_widget_set_size_request(scrollnewmess,724,50);

    downbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_widget_set_size_request(downbox,724,50);
    gtk_widget_set_name(downbox,"downbox");
    gtk_container_add(GTK_CONTAINER(scrollnewmess), downbox);

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

     gtk_widget_show_all(window);
}

