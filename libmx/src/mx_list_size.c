#include "libmx.h"

/*
 * Counts size of linked list.
 */
int mx_list_size(t_list *list) {
    if (list == NULL)
        return -1;

    int size = 0;
    while (list){
        list = list -> next;
        size++;
    }
    return size;
}




