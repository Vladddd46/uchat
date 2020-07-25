#include "server.h"

static chat_message_t *create_message_node(char *sender, char *time, 
                                           char *message, char *msg_type) {
    chat_message_t *node = (chat_message_t *)malloc(sizeof(chat_message_t));
    char *msg;

    if (node == NULL) {
        msg = "create_message_node| Malloc error\n";
        mx_write_to_log(msg, 2);
        exit(1);
    }
    node->sender   = sender;
    node->time     = time;
    node->message  = message;
    node->msg_type = msg_type;
    node->next     = NULL;
    return node;
}

void mx_push_back_message_node(chat_message_t **list, char *sender, char *time, 
                               char *message, char* msg_type) {
    chat_message_t *node = create_message_node(sender, time, message, msg_type);
    chat_message_t *tmp;

    if (*list == NULL)
        *list = node;
    else {
        tmp = *list;
        while(tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = node;
    }
}

