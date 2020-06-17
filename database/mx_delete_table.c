#include "db.h"

static int mx_strlen(char *s) {
    int counter = 0;

    while(s[counter])
        counter++;
    return counter;
}

static char *mx_strcpy(char *dst, char *src) {
    int counter = 0;

    while(src[counter]) {
        dst[counter] = src[counter];
        counter++;
    }
    dst[counter] = '\0';
    return dst;
}

static char *mx_strnew(int size) {
    char *memory = malloc(size + 1);

    if (memory == NULL)
        return NULL;
    for (int i = 0; i < size + 1; i++)
        memory[i] = '\0';
    return memory;
}

static char *mx_strjoin(char *s1, char *s2) {
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

static int mx_callback(void* not_used, int argc, char** argv, char** az_con_name) {
	for(int i = 0; i < argc; i++) {
		printf("%s: %s\n", az_con_name[i], argv[i]);
	}
	return 0;
}

int mx_delete_table(const char* str, char* table) {
	sqlite3* db;
	int exit = sqlite3_open(str, &db);
    char *sql = mx_strjoin("DELETE FROM ", table);
    sql = mx_strjoin(sql, ";");

    sqlite3_exec(db, sql, NULL, NULL, NULL);
    return 0;
}
