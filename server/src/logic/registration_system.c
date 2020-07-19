#include "server.h"

/*
 * Do the registration of the user.
 * Checks, wheather user`s login/password is valid.
 * Forms send_back packet with status of registration.
 */

static int login_exists(sqlite3 *db, char *login) {
    char sql[500];
    bzero(sql, 500);
    sqlite3_stmt *res;
    int check;
    int status = 0;

    sprintf(sql, "SELECT PASSWORD FROM USERS WHERE LOGIN='%s';", login);
    check = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);

    if (sqlite3_column_text(res, 0) != NULL)
        status = 1;
    sqlite3_finalize(res);
    return status;
}

static int nickname_exists(sqlite3 *db, char *nickname) {
    int status = 0;
    char sql[500];
    bzero(sql, 500);
    sqlite3_stmt *res;
    int check;

    sprintf(sql, "SELECT PASSWORD FROM USERS WHERE NICKNAME='%s';", nickname);
    check = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    if (sqlite3_column_text(res, 0) != NULL)
        status = 1;

    sqlite3_finalize(res);
    return status;
}

static int success(sqlite3 *db, char *login ,char *nickname, char *password) {
    char sql[500];
    bzero(sql, 500);
    int st;
    char *message_error;

    sprintf(sql, 
            "INSERT INTO USERS (LOGIN, NICKNAME, PASSWORD) VALUES('%s','%s', '%s');", 
            login, nickname, password);

    st = sqlite3_exec(db, sql, NULL, 0, &message_error);
    dberror(db, st, message_error);
    return 1;
}

/*
 * Try to add(register) user in db. 
 * In case of error returns the corresponding status.
 */
static char *add_user(char *login, char *password, char *nickname) {
    sqlite3 *db = opening_db();
    char *status = NULL;

    if (login_exists(db, login))
        status = "login exist";
    else if (nickname_exists(db, nickname))
        status = "nickname exist";
    else if (success(db, login, nickname, password))
        status = "success";
    sqlite3_close(db);

    if (status == NULL)
        mx_null_value_error("add_user");
    return mx_string_copy(status);
}

static char *form_sendback_packet(char *login, char *password, char *nickname) {
    char  *return_status   = add_user(login, password, nickname);
    cJSON *packet          = cJSON_CreateObject();
    char  *sendback_packet = NULL;

    cJSON *json_value = cJSON_CreateString("reg_s");
    cJSON_AddItemToObject(packet, "TYPE", json_value);
    json_value = cJSON_CreateString(return_status);
    cJSON_AddItemToObject(packet, "STATUS", json_value);
    json_value = cJSON_CreateString(login);
    cJSON_AddItemToObject(packet, "TO", json_value);

    sendback_packet = cJSON_Print(packet);
    if (sendback_packet == NULL)
        mx_null_value_error("form_sendback_packet");

    free(return_status);
    return sendback_packet;
}

char *registration_system(char *packet) {
    char *login           = get_value_by_key(packet, "LOGIN");
    char *password        = get_value_by_key(packet, "PASSWORD");
    char *nickname        = get_value_by_key(packet, "NICKNAME");
    
    if (login == NULL || password == NULL || nickname == NULL)
        mx_null_value_error("registration_system");
    char *sendback_packet = form_sendback_packet(login, password, nickname);

    free(login);
    free(password);
    free(nickname);
    return sendback_packet;
}
