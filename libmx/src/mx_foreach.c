#include "libmx.h"

/*
 * Applies the function f for each element 
 * of the arrayarrof the givensize.
 */

void mx_foreach(int *arr, int size, void (*f)(int)) {
    for (int i = 0; i < size; i++)
        f(arr[i]);
}



