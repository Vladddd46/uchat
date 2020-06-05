#include "libmx.h"

/*
 *  Deletes all whitespace charactes 
 *  from the beginning and the end of str.
 */
char *mx_strtrim(char *str){
    if (str == NULL)
        return NULL;

    int len_str = mx_strlen(str);
    // Skip whitespaces from the beginning.
    int i = 0;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        i++;
    // Skip whitespaces from the end.
    int j = len_str - 1;
    while ((str[j] >= 9 && str[j] <= 13) || str[j] == 32)
        j--;
    // Calculate number of memory to allocate.
    int len_new_str = 0;
    int tmp = i;
    for (; tmp <= j; ++tmp)
        len_new_str++;
    // Allocate memmory
    char *memory = mx_strnew(len_new_str);
    if (memory == NULL)
        return NULL;

    int q = 0;
    while (q < len_new_str){
        memory[q] = str[i];
        i++;
        q++;
    }
    return memory;
}
