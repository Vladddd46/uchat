#include "client.h"

static char* mx_get_login(char* chat_name) {
    char* result = mx_strnew(mx_strlen(chat_name));
    int start = 0;

    for(; *(chat_name + start) != '('; start++);
    start++;
    for(int i = 0; *(chat_name + start + i) != ')'; i++) {
        *(result + i) = *(chat_name + start + i);
    }
    return result;
}

void touch_room_signal(GtkWidget *listbox, void *socket){
    GtkListBoxRow *selectedrow= gtk_list_box_get_selected_row(GTK_LIST_BOX(listbox));
    int indexrow = gtk_list_box_row_get_index(GTK_LIST_BOX_ROW(selectedrow));
    GList *gl = gtk_container_get_children(GTK_CONTAINER(selectedrow));
    GtkGrid *gridchild = gl->data;
    GtkWidget *lab = gtk_grid_get_child_at(gridchild,1,0);

    mx_printstr((char *)gtk_label_get_text(GTK_LABEL(lab)));
    mx_printstr(mx_itoa(indexrow));

    int *test = (int *)socket;
    printf(">>>%d\n", client_context->sockfd);
    char chat_name[80];
    char chat_id[40];
    sprintf(chat_name, "CHATNAME:%s", mx_get_login((char *)gtk_label_get_text(GTK_LABEL(lab))));
    sprintf(chat_id, "CHATID:%d", ++indexrow);

    char *packet = json_packet_former(5, "TYPE:msg_c", chat_name, chat_id, "FROMMSG:5", "TOMSG:15");
    packet = packet_len_prefix_adder(packet);

    send(client_context->sockfd, packet, mx_strlen(packet), 0);
}
