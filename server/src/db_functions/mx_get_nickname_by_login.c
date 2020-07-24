#include "server.h"

char *mx_get_nickname_by_login(char *login) {
    sqlite3 *db = mx_opening_db();
    char sql[200];
    bzero(sql, 200);

    sprintf(sql, "SELECT NICKNAME FROM USERS WHERE LOGIN='%s';", login);
    sqlite3_stmt *res;
    char *nickname;

    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    nickname = mx_string_copy((char *)sqlite3_column_text(res, 0));
    sqlite3_finalize(res);
    sqlite3_close(db);
    return nickname;
}
