#include "libmx.h"

/* 
 * Sorts array <arr> in ascengind order.
 * Returns number of swaps.
 */
int mx_bubble_sort(char **arr, int size){
     int swap_counter = 0;

     for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i- 1; j++)  {
            if (mx_strcmp(arr[i],arr[i + 1]) > 0) {
                char *tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                swap_counter++;
            }
        }
    }
    return swap_counter;
}

