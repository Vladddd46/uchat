#include "libmx.h"

/*
 * Concatenates two strings.
 */
char *mx_strcat(char *restrict s1, char *restrict s2){
    *s1 = *(char *)s1;
    int l1 = mx_strlen(s1);
    int l2 = mx_strlen(s2);

    for(int i = 0; i < l2; i++) {
        s1[l1] = s2[i];
        l1++;
    }
    return s1;
}

