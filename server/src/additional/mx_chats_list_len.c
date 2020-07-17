#include "server.h"

int mx_chats_list_len(chats_t *chat) {
    int len = 0;
    chats_t *tmp = chat;

    while(tmp != NULL) {
        tmp = tmp -> next;
        len++;
    }
    return len;
}
