#include "client.h"

gboolean mx_draw_list_box(void *data){
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
    g_signal_connect(minieventbox,"button-release-event", G_CALLBACK(mx_add_new_friend), minilistbox);
    gtk_list_box_select_row(GTK_LIST_BOX(minilistbox),GTK_LIST_BOX_ROW(minirow));
	g_idle_add ((int (*)(void *))show_widget, miniwindow);
    return 0;
}
