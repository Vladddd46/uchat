#include"libmx.h"

char *mx_strjoin(char *s1, char *s2) {
    if(s1 == NULL && s2 == NULL) return NULL;

    if(s1 == NULL) {
        int len      = mx_strlen(s2);
        char *result = mx_strnew(len);
        result       = mx_strcpy(result ,s2);
        return result;
    }
    if(s2 == NULL) {
        int len      = mx_strlen(s1);
        char *result = mx_strnew(len);
        result       = mx_strcpy(result, s1);
        return result;
    }
    else {
        int len1 = mx_strlen(s1);
        int len2 = mx_strlen(s2);
        char *cat_str  = mx_strnew(len1 + len2);

        for(int i = 0; i < len1; i++)
            cat_str[i] = s1[i];
        for(int i = len1; i < len1 + len2; i++)
            cat_str[i] = s2[i - len1];
        return cat_str;
    }
}
