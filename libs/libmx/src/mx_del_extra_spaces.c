#include "libmx.h"

/*
 * Deletes extra whitespaces between word;
 * Word is sequence of chars separated by whitespace.
 */

// Checks whether char c is whitespace.
static int is_space_custom(char c) {
    if (c == 32 
        || c == 9 
        || c == 10 
        || c == 11 
        || c == 12  
        || c == 13) {
        return 1;
    }
    return 0;
}

char *mx_del_extra_spaces(char *str) {
    if(str == NULL) 
        return NULL;
    int len_str = mx_strlen(str);
    char *str_with_des = mx_strnew(len_str);
    int index = 0;
    int enable = 1;
    int i = 0;

    while(str[i]) {
        if (is_space_custom(str[i]) && enable == 1) {
            str_with_des[index] = str[i];
            enable = 0;
            index++;
        }
        else if (is_space_custom(str[i]) == 0) {
            str_with_des[index] = str[i];
            index++;
            enable = 1;
        }
        i++;
    }
    // cut string to appropriate size;
    char *result = mx_strnew(mx_strlen(str_with_des));
    for (int j = 0; str_with_des[j]; ++j)
        result[j] = str_with_des[j];
    free(str_with_des);
    return result;
}

