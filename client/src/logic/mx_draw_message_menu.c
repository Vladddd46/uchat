#include "client.h"
               
gboolean mx_draw_message_menu(void *data){
    client_context->guinumber = 0;
    client_context->edit = 0;
    client_context->find = 0;
    client_context->sticker = 0;
    client_context->indexrow = -1;
    t_s_glade *gui = (t_s_glade *)data;
    client_context->flag = FALSE;
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
    g_signal_connect(leftmenu,"clicked", G_CALLBACK(mx_draw_edit_profile), NULL);
    newchatbutton = gtk_button_new();
    gtk_box_pack_end(GTK_BOX(leftbox), newchatbutton, TRUE, TRUE, 0);
    iconn = gdk_pixbuf_new_from_file("./media/img/plus_icon.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(iconn);
    gtk_button_set_image (GTK_BUTTON (newchatbutton), icon);
    g_signal_connect(newchatbutton,"clicked", G_CALLBACK(mx_add_new_user), NULL);
    rightbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_widget_set_size_request(rightbox,724,50);
    gtk_widget_set_name(rightbox,"rightbox");
    gtk_fixed_put(GTK_FIXED (fixed), rightbox, 300,0);
    listbox = gtk_list_box_new();
    gtk_widget_set_name(listbox,"listboxleft");
    gtk_widget_set_size_request(scroll,300,718);
    gtk_container_add(GTK_CONTAINER(scroll), listbox);
    g_signal_connect(listbox,"row-activated", G_CALLBACK(mx_touch_room_signal), &client_context->sockfd);
    g_idle_add ((int (*)(void *))show_widget, window);
    return 0;
}
