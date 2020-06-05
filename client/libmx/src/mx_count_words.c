#include "libmx.h"

/*
 * Count words in string.
 * Word is sequence of characters separated by delimiter <c>
 */
int mx_count_words(char *str, char c) {
        if(str == NULL)
        return -1;
    int i = 0;
    int count = 0;

    while(str[i]) {
        if (str[i] != c)
            count++;
        while(str[i] && str[i] != c)
            i++;
        if (str[i])
            i++;
    }
    return count;
}
