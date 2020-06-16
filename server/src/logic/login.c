#include "server.h"

/*
 * Implementation of login functional.
 * 1. Takes received packet of 'login' type.
 * 2. Retrieves needed data from it. (login and password)
 * 3. Make request to db in order to check, whether user with
 *    such login and password exists.
 * 4. Returns the corresponding code.
 */

/*
 * Retrieves data from received packet.
 * Returns array[2] with two strings: 
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

/*
 * Makes request to db in order to check, whether user with
 * such login(data[0]) and such password(data[1]) exists.
 * Returns the corresponding code, defined in header server.h
 */
static int data_validator(char **data) {
    int result = LOGIN_SUCCESS;

    // Forming pattern.
    char *pattern = "SELECT COUNT(*) FROM Users WHERE Login='";
    int len       = (int)strlen(pattern) + (int)strlen(data[0]) + (int)strlen("' AND Password='") + 
    (int)strlen(data[1]) + (int)strlen("';");
    char sql[len];
    sprintf(sql, "%s%s%s%s%s", pattern, data[0], "' AND Password='", data[1],"';");

    // Request to db.
    sqlite3 *db = opening_db();
    sqlite3_stmt *res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res); 
    char *user_exist = (char *)sqlite3_column_text(res, 0);

    // If number of users with such login and password == 0 => no such user.
    if (!strcmp(user_exist, "0"))
        result = LOGIN_FAIL;

    sqlite3_finalize(res);
    sqlite3_close(db);
    return result;
}

int login(int socket, char *packet) {
    /*
     * Retrieves login and password from received packet. 
     * Returns arr[2] = {"login", "password"};
     */
    char **data = data_retriever(packet);
    
    /*
     * Checks, whether user with such login(data[0]) 
     * and such password(data[1]) exists.
     * Returns the corresponding code.
     */
    int status_int = data_validator(data);
    char *status   = mx_itoa(status_int);
    send(socket, status, (int)strlen(status), 0); // Sending login code to the client.

    free(status);
    //free_arr(data) - also it`s needed to free data array but when I did it - free error occured.
    return status_int;
}
