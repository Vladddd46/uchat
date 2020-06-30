#include "libmx.h"

// Pushes new node in front of linked list.
void mx_push_front(t_list **list, void *data){
    t_list *node = (t_list *)malloc(sizeof(t_list));
    node->data = data;
    node->next = *list;
    *list = node;
}
