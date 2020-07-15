#include "crypt.h"

/*
 *  Return amount of characters in a crypted string 
 *  with formant: xx-yy-zz-zz-zz 
 */
int mx_count_string_size(char *str) {
    int counter = 0;

    for(int i = 0; str[i]; i++) {
        if(*(str + i) == '-') {
            counter++;
        }
    }
    counter--;
    return counter;
}
