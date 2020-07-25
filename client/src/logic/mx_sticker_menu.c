#include "client.h"

void mx_sticker_menu(GtkWidget* widget, gpointer data){
    if (client_context->sticker == 0) {
        client_context->sticker = 1;
        stickerwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_widget_set_name(stickerwindow,"stickerwindow");
        gtk_window_set_resizable (GTK_WINDOW(stickerwindow), FALSE);
        gtk_window_set_transient_for (GTK_WINDOW(stickerwindow),GTK_WINDOW(window));
        gtk_window_set_title(GTK_WINDOW(stickerwindow),"Stickers menu");
        gtk_widget_set_size_request(GTK_WIDGET(stickerwindow),400,300);
        g_signal_connect(stickerwindow,"delete-event",G_CALLBACK(mx_stickerbool),NULL);

        stickerfixed = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(stickerwindow),stickerfixed);

        stickerebox = gtk_event_box_new();
        gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,0,0);
        g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/1.png");
        g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(mx_sticker_send_system),NULL);


        GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/1.png",NULL);
        iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
        stickerimage = gtk_image_new_from_pixbuf(iconn);
        gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

        stickerebox = gtk_event_box_new();
        gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,100,0);
        g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/2.png");
        g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(mx_sticker_send_system),NULL);

        iconn = gdk_pixbuf_new_from_file("./media/img/2.png",NULL);
        iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
        stickerimage = gtk_image_new_from_pixbuf(iconn);
        gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

        stickerebox = gtk_event_box_new();
        gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,200,0);
        g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/3.png");
        g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(mx_sticker_send_system),NULL);

        iconn = gdk_pixbuf_new_from_file("./media/img/3.png",NULL);
        iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
        stickerimage = gtk_image_new_from_pixbuf(iconn);
        gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

        stickerebox = gtk_event_box_new();
        gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,300,0);
        g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/4.png");
        g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(mx_sticker_send_system),NULL);

        iconn = gdk_pixbuf_new_from_file("./media/img/4.png",NULL);
        iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
        stickerimage = gtk_image_new_from_pixbuf(iconn);
        gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

         stickerebox = gtk_event_box_new();
        gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,0,100);
        g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/5.png");
        g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(mx_sticker_send_system),NULL);

        iconn = gdk_pixbuf_new_from_file("./media/img/5.png",NULL);
        iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
        stickerimage = gtk_image_new_from_pixbuf(iconn);
        gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

         stickerebox = gtk_event_box_new();
        gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,100,100);
        g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/6.png");
        g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(mx_sticker_send_system),NULL);

        iconn = gdk_pixbuf_new_from_file("./media/img/6.png",NULL);
        iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
        stickerimage = gtk_image_new_from_pixbuf(iconn);
        gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

         stickerebox = gtk_event_box_new();
        gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,200,100);
        g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/7.png");
        g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(mx_sticker_send_system),NULL);

        iconn = gdk_pixbuf_new_from_file("./media/img/7.png",NULL);
        iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
        stickerimage = gtk_image_new_from_pixbuf(iconn);
        gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

         stickerebox = gtk_event_box_new();
        gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,300,100);
        g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/8.png");
        g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(mx_sticker_send_system),NULL);

        iconn = gdk_pixbuf_new_from_file("./media/img/8.png",NULL);
        iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
        stickerimage = gtk_image_new_from_pixbuf(iconn);
        gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

         stickerebox = gtk_event_box_new();
        gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,0,200);
        g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/9.png");
        g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(mx_sticker_send_system),NULL);

        iconn = gdk_pixbuf_new_from_file("./media/img/9.png",NULL);
        iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
        stickerimage = gtk_image_new_from_pixbuf(iconn);
        gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

        stickerebox = gtk_event_box_new();
        gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,100,200);
        g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/10.png");
        g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(mx_sticker_send_system),NULL);

        iconn = gdk_pixbuf_new_from_file("./media/img/10.png",NULL);
        iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
        stickerimage = gtk_image_new_from_pixbuf(iconn);
        gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

         stickerebox = gtk_event_box_new();
        gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,200,200);
        g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/11.png");
        g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(mx_sticker_send_system),NULL);

        iconn = gdk_pixbuf_new_from_file("./media/img/11.png",NULL);
        iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
        stickerimage = gtk_image_new_from_pixbuf(iconn);
        gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);

         stickerebox = gtk_event_box_new();
        gtk_fixed_put(GTK_FIXED(stickerfixed),stickerebox,300,200);
        g_object_set_data(G_OBJECT(stickerebox),"sticker path","./media/img/12.png");
        g_signal_connect(stickerebox,"button-press-event", G_CALLBACK(mx_sticker_send_system),NULL);

        iconn = gdk_pixbuf_new_from_file("./media/img/12.png",NULL);
        iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
        stickerimage = gtk_image_new_from_pixbuf(iconn);
        gtk_container_add(GTK_CONTAINER(stickerebox),stickerimage);
        g_idle_add ((int (*)(void *))show_widget, stickerwindow);
  }
}
