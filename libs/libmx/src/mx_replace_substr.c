#include "libmx.h"

static void get_all_lengths(int *len_s, int *len_r, char *sub, char *replace) {
    *len_s = mx_strlen(sub);
    *len_r = mx_strlen(replace);
}

static void not_sub_case( char **s,  char **sub, char **buf) {
    if (*s != mx_strstr(*s, *sub)) {
        **buf = **s;
        (*buf)++;
        (*s)++;
    }
}

char *mx_replace_substr( char *str,  char *sub,
                         char *replace) {
    char *buf1 = NULL;
    char *buf2 = NULL;
     char *s = str;
    int len_s = 0;
    int len_r = 0;

    if ((!str) || (!sub) || (!replace))
        return NULL;
    get_all_lengths(&len_s, &len_r, (char *)sub, (char *)replace);
    buf1 = mx_strnew(mx_strlen(s) + (len_r - len_s) * mx_count_substr(s, sub));
    buf2 = buf1;
    while (*s) {
        not_sub_case(&s, &sub, &buf2);
        if (s == mx_strstr(s, sub)) {
            buf2 = mx_strcat(buf2, replace);
            buf2 += len_r;
            s += len_s;
        }
    }
    return buf1;
}

