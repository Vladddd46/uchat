#include "libmx.h"

/*
 * Deletes node in the back of linked list.
 */
void mx_pop_back(t_list **head){
    t_list *node_to_delete;
    t_list *prelast = *head;

    while (prelast->next->next != NULL)
        prelast = prelast->next;
    node_to_delete = prelast->next;
    prelast->next  = NULL;
    free(node_to_delete->data);
    free(node_to_delete);
}

