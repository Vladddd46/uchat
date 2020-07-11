#include "client.h"

void touch_room_signal(GtkWidget *listbox, gpointer data){
    GtkListBoxRow *selectedrow= gtk_list_box_get_selected_row(GTK_LIST_BOX(listbox));
    int indexrow = gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(selectedrow));
    GList *gl = gtk_container_get_children(GTK_CONTAINER(selectedrow));
    GtkGrid *gridchild = gl->data;
    GtkWidget *lab = gtk_grid_get_child_at(gridchild,1,0);

    mx_printstr((char *)gtk_label_get_text(GTK_LABEL(lab)));
    mx_printstr(mx_itoa(indexrow));
    // cJSON *packet = cJSON_CreateObject();
    // char  *packet_str = NULL;

    // cJSON *typ = cJSON_CreateString("msg_c");
    // cJSON *type = cJSON_CreateString("0");
    // cJSON *nick = cJSON_CreateString("30");
    // cJSON *sender = cJSON_CreateString("1");

    // cJSON_AddItemToObject(packet, "TYPE", typ);
    // cJSON_AddItemToObject(packet, "CHATID", sender);
    // cJSON_AddItemToObject(packet, "FROM", type);
    // cJSON_AddItemToObject(packet, "TO", nick);
    // packet_str = mx_str_copy(cJSON_Print(packet));
    // cJSON_Delete(packet);
    // send(client_context->sockfd, packet_str, mx_strlen(packet_str), 0);
}
