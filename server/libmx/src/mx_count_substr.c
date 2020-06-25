#include "libmx.h"

/*
 * Counts number of occurrences of substring in a string.
 */
int mx_count_substr(char *str, char *sub) {
    if (str == NULL || sub == NULL)
        return -1;

    int len_sub = mx_strlen(sub);
    int i = 0;
    int counter = 0;
    
    // Walk through each symbol in str.
    while(str[i]){

        // first symbols in sub and str are identic.
        if (str[i] == sub[0]) {
            // further check of symbols identity.
            int j = 0;
            int tmp = i;
            while (str[tmp] && sub[j] && str[tmp] == sub[j]) {
                // if j == lenghth of sub => match is found.
                if (j == len_sub - 1){
                    counter++;
                    break;
                }
                j++;
                tmp++;
            }
        }
        i++;
    }
    return counter;
}
