#include "libmx.h"

/*
 * Replaces all occurances of sub in str with replace.
 */
char *mx_replace_substr(char *str, char *sub, char *replace){
    // Len of all objects.
    int len_str     = mx_strlen(str);   
    int len_sub     = mx_strlen(sub);
    int len_replace = mx_strlen(replace);
    // Calculate difference in mem. to allocate appropriate mem.
    int difference = len_replace - len_sub;
    int number_of_substr = mx_count_substr(str, sub);
    int difference_in_memory = difference * number_of_substr;
    // Allocate mem. for new string.
    char *new_str = mx_strnew(len_str + difference_in_memory);

    // Algorithm, which do the replace.
    int str_step = 0;
    int end_of_new_str = 0;
    while(str[str_step]) {
        // First symbols are identical.
        if (str[str_step] == sub[0]) {
            // Further checking of identity.
            int j = 0;
            int tmp = str_step;
            while (str[tmp] == sub[j]){
                // sub is found. add replace in new_str and hop with sub len.
                if (j == len_sub - 1) {
                    int repl = 0;
                    while(replace[repl]) {
                        new_str[end_of_new_str] = replace[repl];
                        repl++;
                        end_of_new_str++;
                    } 
                    str_step += len_sub;
                }
                j++;
                tmp++;
            }
        }
        else {
            new_str[end_of_new_str] = str[str_step];
            end_of_new_str++;
            str_step++;
        }
    }
    return new_str;
}


