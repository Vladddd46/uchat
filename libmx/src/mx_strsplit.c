#include "libmx.h"

/*
 * Converts a strings  to the NULL-terminated array of words 
 * and frees all unused memory.
 * Returns NULL-terminated array of strings in case of success or NULL
 * if the strings does not exist or conversion fails.
 */
char **mx_strsplit(char *s, char c){
    // Calculate mem. for array
    int counter1 = 0;
    int len = 0;
    while (s[counter1]) {
        if (s[counter1] != c)
            len++;
        counter1++;
    }
    char **result = (char **)malloc(sizeof(char *) * len);
    result[len] = NULL;

    int i = 0;
    int tmp;
    int num_of_words = 0;
    while (s[i]) {
        if(s[i] != c) {
            tmp = i;
            while (s[i] != c && s[i])
                i++;
            int len_word = i - tmp;
            char *word = mx_strnew(len_word);
            for (int j = 0; tmp < i; tmp++, j++)
                word[j] = s[tmp];
            result[num_of_words] = word;
            num_of_words++;
        }
        else
            i++;
    }
    result[num_of_words] = NULL;
    return result;
}
