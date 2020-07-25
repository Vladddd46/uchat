#include "client.h"

gboolean create_message(void *data){
    t_s_glade *pack = (t_s_glade *)data; 
    GtkAdjustment *adj;
    char *nameuser = client_context->username;
    char *sender = get_value_by_key(pack->pack,mx_strjoin("SENDER",mx_itoa(pack->number)));
    int messagenum = atoi(get_value_by_key(pack->pack,mx_strjoin("ID",mx_itoa(pack->number))));
    char *messagetext = get_value_by_key(pack->pack,mx_strjoin("MESSAGE",mx_itoa(pack->number)));
    char *timemessage = get_value_by_key(pack->pack,mx_strjoin("TIME",mx_itoa(pack->number)));
    char *type = get_value_by_key(pack->pack,mx_strjoin("MSGTYPE",mx_itoa(pack->number))); 

    adj = gtk_adjustment_new(10000, 100000, 1, 1000, 10000, 10000);
    row = gtk_list_box_row_new();
    ebox = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(row), ebox);
    gtk_list_box_row_set_selectable (GTK_LIST_BOX_ROW(row),FALSE);
    gtk_list_box_insert (GTK_LIST_BOX(listboxmess),row,messagenum);

    horizontalbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_container_add(GTK_CONTAINER(ebox), horizontalbox);

    messagebox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    if (!strcmp(nameuser,sender))
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

    labellmenu = gtk_label_new(sender);
    gtk_widget_set_name(labellmenu,"labellmenu");
    gtk_box_pack_start(GTK_BOX(verticalbox),labellmenu, FALSE, FALSE, 0);
    if(mx_strcmp(type,"sticker") == 0){
        iconn = gdk_pixbuf_new_from_file(messagetext,NULL);
        iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
        stickermessage = gtk_image_new_from_pixbuf(iconn);
        gtk_box_pack_start(GTK_BOX(verticalbox),stickermessage, FALSE, FALSE, 0);
    }
    else{
        if (messagetext[0] == '\\') {
            if (messagetext[1] == 'b'){
                char *messagetextnew = mx_strnew(mx_strlen(&messagetext[2]));
                mx_strcpy(messagetextnew,&messagetext[2]);
                labellmenu2 = gtk_label_new(messagetextnew);
                gtk_widget_set_name(labellmenu2,"labellmenu2bold");
                gtk_box_pack_start(GTK_BOX(verticalbox),labellmenu2, FALSE, FALSE, 0); 
            }
            else
            if (messagetext[1] == 'i'){
                char *messagetextnew = mx_strnew(mx_strlen(&messagetext[2]));
                mx_strcpy(messagetextnew,&messagetext[2]);
                labellmenu2 = gtk_label_new(messagetextnew);
                gtk_widget_set_name(labellmenu2,"labellmenu2italic");
                gtk_box_pack_start(GTK_BOX(verticalbox),labellmenu2, FALSE, FALSE, 0); 
            }
            else
            if (messagetext[1] == 'r'){
                char *messagetextnew = mx_strnew(mx_strlen(&messagetext[2]));
                mx_strcpy(messagetextnew,&messagetext[2]);
                labellmenu2 = gtk_label_new(messagetextnew);
                gtk_widget_set_name(labellmenu2,"labellmenu2red");
                gtk_box_pack_start(GTK_BOX(verticalbox),labellmenu2, FALSE, FALSE, 0); 
            }
            else
            if (messagetext[1] == '1'){
                char *messagetextnew = mx_strnew(mx_strlen(&messagetext[2]));
                mx_strcpy(messagetextnew,&messagetext[2]);
                labellmenu2 = gtk_label_new(messagetextnew);
                gtk_widget_set_name(labellmenu2,"labellmenu2small");
                gtk_box_pack_start(GTK_BOX(verticalbox),labellmenu2, FALSE, FALSE, 0); 
            }
            else
            if (messagetext[1] == 'y'){
                char *messagetextnew = mx_strnew(mx_strlen(&messagetext[2]));
                mx_strcpy(messagetextnew,&messagetext[2]);
                labellmenu2 = gtk_label_new(messagetextnew);
                gtk_widget_set_name(labellmenu2,"labellmenu2yellow");
                gtk_box_pack_start(GTK_BOX(verticalbox),labellmenu2, FALSE, FALSE, 0); 
            }
            else
            if (messagetext[1] == '9'){
                char *messagetextnew = mx_strnew(mx_strlen(&messagetext[2]));
                mx_strcpy(messagetextnew,&messagetext[2]);
                labellmenu2 = gtk_label_new(messagetextnew);
                gtk_widget_set_name(labellmenu2,"labellmenu2big");
                gtk_box_pack_start(GTK_BOX(verticalbox),labellmenu2, FALSE, FALSE, 0); 
            }
            else{
                labellmenu2 = gtk_label_new(messagetext);
                gtk_widget_set_name(labellmenu2,"labellmenu2");
                gtk_box_pack_start(GTK_BOX(verticalbox),labellmenu2, FALSE, FALSE, 0);
            }
        }
        else{
            labellmenu2 = gtk_label_new(messagetext);
            gtk_widget_set_name(labellmenu2,"labellmenu2");
            gtk_box_pack_start(GTK_BOX(verticalbox),labellmenu2, FALSE, FALSE, 0);
        }
        }

    labellmenu3 = gtk_label_new(timemessage);
    gtk_box_pack_start(GTK_BOX(messagebox),labellmenu3, FALSE, FALSE, 0);
    g_idle_add ((int (*)(void *))show_widget, window);
    gtk_scrolled_window_set_vadjustment(GTK_SCROLLED_WINDOW(scrollmess), adj);
    client_context->counter+=1;
    pack->number+=1;
    return 0;
}
