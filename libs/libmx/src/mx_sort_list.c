#include "libmx.h"

/*
 * Sorts the list’s contents in ascending order. 
 * Func. cmp returns true if a > b and false in other cases.
 */

/*
Example:
bool cmp1(int *a, int *b){  
    printf("%d\n", *(int *)a);
    return *a>*b;
}
*/

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
    t_list *sorted_lst = lst;
    int lst_len = mx_list_size(sorted_lst);
    bool  result;
    
    for (int i = 0; i < lst_len - 1; ++i) {
        t_list *tmp_sorted_lst = lst;
        
        for (int j = 0; j < lst_len - 1; ++j) {
            result = cmp(tmp_sorted_lst->data, tmp_sorted_lst -> next -> data);
            if (result) {   
                void *tmp = tmp_sorted_lst->data;
                tmp_sorted_lst->data = tmp_sorted_lst->next->data;
                tmp_sorted_lst->next->data = tmp;
            }
            tmp_sorted_lst = tmp_sorted_lst->next;
        }
    }
    return lst;
}
