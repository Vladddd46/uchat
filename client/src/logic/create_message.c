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

void edit_message(GtkWidget *widget, GtkWidget *message){
    if (flag == FALSE) {
    char *editbuff = (char *)gtk_label_get_text(GTK_LABEL(message));
    gtk_widget_hide(newmessedgentry);
    editmessedgentry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(editmessedgentry),"Write a message...");
    gtk_widget_set_name(editmessedgentry,"newmessedgentry");
    gtk_box_pack_start(GTK_BOX(downbox),editmessedgentry, TRUE, TRUE, 0);
    gtk_entry_set_text(GTK_ENTRY(editmessedgentry),editbuff);
    g_idle_add ((int (*)(void *))show_widget, editmessedgentry);
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
    g_idle_add ((int (*)(void *))show_widget, newmessedgentry);
    flag = FALSE;

} 

gboolean create_message(void *data){
    t_s_glade *pack = (t_s_glade *)data; 
  GtkAdjustment *adj;

    char *nameuser = client_context->username;
    char *sender = get_value_by_key(pack->pack,mx_strjoin("SENDER",mx_itoa(pack->number)));
    int messagenum = atoi(get_value_by_key(pack->pack,mx_strjoin("ID",mx_itoa(pack->number))));
    char *messagetext = get_value_by_key(pack->pack,mx_strjoin("MESSAGE",mx_itoa(pack->number)));
    char *timemessage = get_value_by_key(pack->pack,mx_strjoin("TIME",mx_itoa(pack->number)));    // почисти память

    adj = gtk_adjustment_new(10000, 100000, -1000, 100, 10000, 10000);
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
    g_idle_add ((int (*)(void *))show_widget, edit);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), edit);
    g_signal_connect (edit, "activate", G_CALLBACK (edit_message), labellmenu2);

    delet = gtk_menu_item_new_with_label("Delete");
    g_idle_add ((int (*)(void *))show_widget, delet);
    gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu), delet);  
    g_signal_connect (delet, "activate", G_CALLBACK (delete_message), row);

    
    g_idle_add ((int (*)(void *))show_widget, window);
    //gtk_widget_show_all(window);
    gtk_scrolled_window_set_vadjustment(GTK_SCROLLED_WINDOW(scrollmess), adj);
    client_context->counter+=1;
    pack->number+=1;
    return 0;
}

static char *mx_get_time() {
    time_t rawtime;
    struct tm * timeinfo;
    char *date = NULL;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    date = asctime (timeinfo);
    return date;
}

gboolean create_message_system(void *data){
    char *message_from_user = get_text_of_textview(newmessedgentry);
    if (message_from_user == NULL) {
        mx_null_error("142: create_message_system error");
    }
    char *processed_msg_from_user = mx_change_offensive_words(message_from_user);
     if (processed_msg_from_user == NULL) {
        mx_null_error("145: create_message_system error");
    }
    char *all_users = client_context->allusers;

    char  *packet_str = NULL;
    cJSON *packet = cJSON_CreateObject();
    cJSON *type   = cJSON_CreateString("add_msg_c");
    char *current_time = mx_get_time();
    if (current_time == NULL)
         mx_null_error("150: current_time is NULL");
    cJSON *time        = cJSON_CreateString(current_time);
    cJSON *msg         = cJSON_CreateString(processed_msg_from_user);
    cJSON *allusers    = cJSON_CreateString(all_users);
    cJSON *message_id  = cJSON_CreateString("0");
    int chat_id_client = client_context->indexrow;
    cJSON *chat_id     = cJSON_CreateString(client_context->mas[client_context->indexrow]);
    cJSON *username    = cJSON_CreateString(client_context -> username);
    
    cJSON_AddItemToObject(packet, "TYPE", type);
    cJSON_AddItemToObject(packet, "MESSAGEID", message_id);
    cJSON_AddItemToObject(packet, "TIME", time);
    cJSON_AddItemToObject(packet, "TO", allusers);
    cJSON_AddItemToObject(packet, "MESSAGE", msg);
    cJSON_AddItemToObject(packet, "CHATID", chat_id);
    cJSON_AddItemToObject(packet, "SENDER", username);

    packet_str = mx_string_copy(cJSON_Print(packet));

    char *packet_str1 =  packet_len_prefix_adder(packet_str);
    printf("[outcomming packet]%s\n", packet_str1);
    send(client_context->sockfd, packet_str1, (int)strlen(packet_str1), 0);
    free(packet_str);
    free(packet_str1);
    return 0;
}
