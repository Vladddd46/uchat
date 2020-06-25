#include "libmx.h"

/*
 * Finds index of substr.
 */
int mx_get_substr_index(char *str, char *sub){
    if (str == NULL || sub == NULL)
        return -2;
    int len_sub = mx_strlen(sub);
    int i = 0;
    
    while(str[i]){
        // Indentity of first symbols are found.
        if (str[i] == sub[0]){

            // Checking further identity
            int j = 0;
            int tmp = i;
            while (str[tmp] == sub[j]){
                // Substr found.
                if (j == len_sub - 1)
                    return i;
                j++;
                tmp++;
            }
        }
        i++;
    }
    return -1;
}







