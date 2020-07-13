#include "client.h"

bool  flag = FALSE;

int show_popup(GtkWidget *widget, GdkEvent *event) {
    const gint RIGHT_CLICK = 3;
    
    if (event->type == GDK_BUTTON_PRESS) {
        GdkEventButton *bevent = (GdkEventButton *) event;
        if (bevent->button == RIGHT_CLICK) {      
            gtk_menu_popup_at_pointer(GTK_MENU(widget), event);
            return TRUE;
        }
    }
    return FALSE;
}

void delete_message(GtkWidget *widget, GtkWidget *message){
    if (flag == FALSE) {
        gtk_widget_destroy(message);
    }
}

void edit_message (GtkWidget *widget, GtkWidget *message){
    if (flag == FALSE) {
    char *editbuff = (char *)gtk_label_get_text(GTK_LABEL(message));
    gtk_widget_hide(newmessedgentry);
    editmessedgentry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(editmessedgentry),"Write a message...");
    gtk_widget_set_name(editmessedgentry,"newmessedgentry");
    gtk_box_pack_start(GTK_BOX(downbox),editmessedgentry, TRUE, TRUE, 0);
    gtk_entry_set_text(GTK_ENTRY(editmessedgentry),editbuff);
    gtk_widget_show(editmessedgentry);
    g_signal_connect(editmessedgentry, "activate", G_CALLBACK(end_message), message);
    
    editbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_widget_set_size_request(editbox,724,50);
    gtk_widget_set_name(editbox,"editbox");
    gtk_fixed_put(GTK_FIXED(fixed), editbox, 300,668);
    
    flag = TRUE;
    }
}

//отправка редактируемого сообщения
void end_message (GtkWidget *widget, GtkWidget *message){
    
    char *editbuff = (char *)gtk_entry_get_text(GTK_ENTRY(editmessedgentry));
    gtk_label_set_text(GTK_LABEL(message),editbuff);
    gtk_widget_destroy(editmessedgentry);
    gtk_widget_show(newmessedgentry);
    flag = FALSE;

}

void create_message(GtkWidget *newmessedgentry, struct struct_type parm){
  GtkWidget *row;
  GtkAdjustment *adj;

    char *nameuser = get_value_by_key(parm.pack,"TO");
    char *chatname = get_value_by_key(parm.pack,mx_strjoin("SENDER",mx_itoa(parm.number)));
    int messagenum = atoi(get_value_by_key(parm.pack,mx_strjoin("ID",mx_itoa(parm.number))));
    char *messagetext = get_value_by_key(parm.pack,mx_strjoin("MESSAGE",mx_itoa(parm.number)));
    char *timemessage = get_value_by_key(parm.pack,mx_strjoin("TIME",mx_itoa(parm.number)));
    adj = gtk_adjustment_new(10000, 10000, 1, 10000, 10000, 100000);
    row = gtk_list_box_row_new();
    ebox = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(row), ebox);
    gtk_list_box_row_set_selectable (GTK_LIST_BOX_ROW(row),FALSE);
    gtk_list_box_insert (GTK_LIST_BOX(listboxmess),row,messagenum);

    horizontalbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_container_add(GTK_CONTAINER(ebox), horizontalbox);

    messagebox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    if (!strcmp(nameuser,chatname))
        gtk_box_pack_end(GTK_BOX(horizontalbox),messagebox, FALSE, FALSE, 0);
    else
        gtk_box_pack_start(GTK_BOX(horizontalbox),messagebox, FALSE, FALSE, 0);
    gtk_widget_set_name(messagebox,"message");
    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/pokemon-2.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(iconn);
    gtk_box_pack_start(GTK_BOX(messagebox),icon, FALSE, FALSE, 0);

    verticalbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_box_pack_start(GTK_BOX(messagebox),verticalbox, FALSE, FALSE, 0);

    labellmenu = gtk_label_new(chatname);
    gtk_widget_set_name(labellmenu,"labellmenu");
    gtk_box_pack_start(GTK_BOX(verticalbox),labellmenu, FALSE, FALSE, 0);

    //char *messageBuff = get_text_of_textview(newmessedgentry);
    labellmenu2 = gtk_label_new(messagetext);
    gtk_widget_set_name(labellmenu2,"labellmenu2");
    gtk_box_pack_start(GTK_BOX(verticalbox),labellmenu2, FALSE, FALSE, 0);

    labellmenu3 = gtk_label_new(timemessage);
    gtk_box_pack_start(GTK_BOX(messagebox),labellmenu3, FALSE, FALSE, 0);

 
 //menu with edit and delete button
    fileMenu = gtk_menu_new();
    g_signal_connect_swapped(G_OBJECT(ebox), "button-press-event", G_CALLBACK(show_popup), fileMenu);

    edit = gtk_menu_item_new_with_label("Edit");
    gtk_widget_show(edit);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), edit);
    g_signal_connect (edit, "activate", G_CALLBACK (edit_message), labellmenu2);

    delet = gtk_menu_item_new_with_label("Delete");
    gtk_widget_show (delet);
    gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu), delet);  
    g_signal_connect (delet, "activate", G_CALLBACK (delete_message), row);

    gtk_widget_show_all(window);
    //gtk_scrolled_window_set_vadjustment(GTK_SCROLLED_WINDOW(scrollmess), adj);
    printf("%s\n",">>>>>>>" );
}


