#include "client.h"

static int n = 0;

gboolean create_row(void *data){
    char *pack =(char *)data;
    printf("%s\n",pack );
    //struct struct_type *parm =(struct struct_type *)data;
    char *chatname = get_value_by_key(pack,mx_strjoin("CHATNAME=",mx_itoa(n)));
    char *lastmessage = get_value_by_key(pack,mx_strjoin("LASTMESSAGE=",mx_itoa(n)));
    row = gtk_list_box_row_new();
    gtk_widget_set_name(row,"chatrow");
    gtk_list_box_insert (GTK_LIST_BOX(listbox),row,n);
    n++;

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

    // labellmenu3 = gtk_label_new("Yesterday");
    // gtk_grid_attach(GTK_GRID(gridmenu), labellmenu3, 2, 0, 1, 1);
    // gtk_widget_set_name(labellmenu3,"labellmenu3");

    gtk_widget_show_all(window);
    return 0;
}
