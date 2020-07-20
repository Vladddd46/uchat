#include "utils.h"

/*
 * change offensive words in message.
 */
char *mx_change_offensive_words(char *str) {
    char *words[29] = {"fuck", "slut", "prostitute", "блеать",  "сука", "соси",
                  "уебан", "пидор", "долбоеб", "хуй", "гавно", "лох", "сука",
                  "пососи", "ретард", "pidor", "гамосек", "сосунок", "даун",
                  "аутист", "блядь", "ебать", "тупо", "шлюха", "деби", "гей",
                  "отбитый", "конча", "гандон"};
    int indx;
    char *res = mx_string_copy(str);
    char *tmp;

    for(int i = 0; i < 28; i++) {
        indx = mx_get_substr_index(str, words[i]);
        if (indx != -2 && indx != -1) {
            tmp = mx_replace_substr(res, words[i], "****");
            free(res);
            res = tmp;
        }
    }
    return res;
}
