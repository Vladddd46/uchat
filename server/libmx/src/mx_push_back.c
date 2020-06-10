#include "libmx.h"

// Pushes node in the back of linked list.
void mx_push_back(t_list **list, void *data) {
    t_list *node = mx_create_node(data);

    // Go through each node till last node.
    t_list *last_element = *list;
    while (last_element->next != NULL)
        last_element = last_element->next;
    // Adding new node to the end
    last_element->next = node;
}
