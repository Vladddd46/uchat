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

    sprintf(sql, "INSERT INTO USERS (LOGIN, NICKNAME, PASSWORD) VALUES('%s', '%s', '%s');", login, nickname, password);
    st = sqlite3_exec(db, sql, NULL, 0, &message_error);
    dberror(db, st, message_error);
    return 1;
}

/*
 * Try to add(register) user in db. 
 * In case of error returns the corresponding status.
 */
static char *mx_add_user(char *login, char *password, char *nickname) {
    sqlite3 *db = opening_db();
    char *status = NULL;

    if (login_exists(db, login))
        status = mx_string_copy("STATUS:login exist");
    else if (nickname_exists(db, nickname))
        status = mx_string_copy("STATUS:nickname exist");
    else if (success(db, login, nickname, password))
        status = mx_string_copy("STATUS:success");

    sqlite3_close(db);
    return status;
}

char *registration_system(char *packet) {
    char *login           = get_value_by_key(packet, "LOGIN");
    char *password        = get_value_by_key(packet, "PASSWORD");
    char *nickname        = get_value_by_key(packet, "NICKNAME");
    char *return_status   = mx_add_user(login, password, nickname);
    char *to              = mx_strjoin("TO:", login);
    char *sendback_packet = json_packet_former(3, "TYPE:reg_s", return_status, to);

    free(login);
    free(password);
    free(nickname);
    free(return_status);
    free(to);
    return sendback_packet;
}
