#include "server.h"

/*
 * Returns array of two strings. 
 * array[0] = login. array[1] = password
 */
static char **data_retriever(char *packet) {
    char **data = mx_new_strarr(2);
    cJSON *parsed_str = cJSON_Parse(packet);
    char *msg = "Json Parsing error\n";
    if (parsed_str == NULL) {
        write(2, msg, (int)strlen(msg));
        exit(1);
    }
    cJSON *login = cJSON_GetObjectItemCaseSensitive(parsed_str, "LOGIN: ");
    if (cJSON_IsString(login) && (login->valuestring != NULL))
        data[0] = mx_string_copy(login->valuestring);

    cJSON *password = cJSON_GetObjectItemCaseSensitive(parsed_str, "PASSWORD: ");
    if (cJSON_IsString(password) && (password->valuestring != NULL))
        data[1] = mx_string_copy(password->valuestring);

    cJSON_Delete(parsed_str);
    return data;
}

static int data_validator(char **data) {
    int result = LOGIN_SUCCESS;

    sqlite3 *db = opening_db();

    // Forming pattern.
    char *pattern = "SELECT COUNT(*) FROM Users WHERE Login='";
    int len = (int)strlen(pattern) + (int)strlen(data[0]);
    char sql[len];
    sprintf(sql, "%s%s%s", pattern, data[0], "';");


    sqlite3_stmt *res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    sqlite3_step(res); 
    char *s = (char *)sqlite3_column_text(res, 0);
    if (!strcmp(s, "0")) {
        printf("%s\n", "No user with such login");
        result = LOGIN_WRONG_LOGIN;
    }


    sqlite3_finalize(res);
    sqlite3_close(db);
    return result;
}


int login(int socket, char *packet) {

    /*
     * Retrieves login and password from database. 
     * Returns arr[2] = {"login", "password"};
     */
    char **data = data_retriever(packet);
    int  status = data_validator(data);

    printf("%d\n", status);

    return 0;
}
