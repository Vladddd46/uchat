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

static char* mx_insert_all_args(char* name, char* time) {
	char* request = mx_strjoin("INSERT INTO USERS (NAME, TIME) VALUES('", name);

    request = mx_strjoin(request, "', '");
    request = mx_strjoin(request, time);
    request = mx_strjoin(request, "');");
    // printf("%s", request);
    return request;
}

int mx_insert_data(const char *str, char* name, char* time) {
    sqlite3 *db;
    char *message_error;
    int exit = sqlite3_open(str, &db);
    char* sql = mx_insert_all_args(name, time);

    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    if(exit != SQLITE_OK) {
    	printf("Error insert");
    	sqlite3_free(message_error);
    }
    return 0;
}
