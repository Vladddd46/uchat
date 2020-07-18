#include "server.h"

static users_list_t *create_users_list_node(int id, 
                                            char *login, 
                                            char *nickname) {
    users_list_t *node = (users_list_t *)malloc(sizeof(users_list_t));
    char *msg;

    if (node == NULL) {
        msg = "create_users_list_node| Malloc Error\n";
        write(2, msg, (int)strlen(msg));
        exit(1);
    }
    node->id       = id;
    node->login    = login;
    node->nickname = nickname; 
    node->next     = NULL;
    return node;
}

void mx_push_users_list_node_back(users_list_t **list, int id, 
                                  char *login, char *nickname) {
    users_list_t *node = create_users_list_node(id, login, nickname);
    users_list_t *tmp;

    if (*list == NULL)
        *list = node;
    else {
        tmp = *list;
        while(tmp->next != NULL)
            tmp = tmp->next;
        tmp = node;
    }
}
