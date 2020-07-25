#include "client.h"


gboolean create_row(void *data){
     t_s_glade *gui = (t_s_glade *)data;
    char *chatname = get_value_by_key(gui->pack,mx_strjoin("CHATNAME=",mx_itoa(gui->number)));
    char *lastmessage = get_value_by_key(gui->pack,mx_strjoin("LASTMESSAGE=",mx_itoa(gui->number)));
    row = gtk_list_box_row_new();
    gtk_widget_set_name(row,"chatrow");
    gtk_list_box_insert (GTK_LIST_BOX(listbox),row,gui->number); 
    g_object_set_data(G_OBJECT(row),"row number",&(gui->number));
    client_context->mas[gui->number] = get_value_by_key(gui->pack, mx_strjoin("CHATID=",mx_itoa(gui->number)));
    gridmenu = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(row), gridmenu);
    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/pokemon-2.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(iconn);
    gtk_grid_attach(GTK_GRID(gridmenu), icon, 0, 0, 1, 2);
    labellmenu = gtk_label_new(chatname);
    gtk_widget_set_name(labellmenu,"labellmenu");
    gtk_grid_attach(GTK_GRID(gridmenu), labellmenu, 1, 0, 1, 1);
    labellmenu2 = gtk_label_new(lastmessage);
    gtk_widget_set_name(labellmenu2,"labellmenu2");
    gtk_grid_attach(GTK_GRID(gridmenu), labellmenu2, 1, 1, 1, 1);
    gui->number+=1;
    client_context->guinumber = gui->number;
    g_idle_add ((int (*)(void *))show_widget, window);
    return 0;
}
