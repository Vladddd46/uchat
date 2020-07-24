#include "server.h"

/*
 * Initialize database, if it does not exist.
 * Creates user(login = admin, password = qwerty) by default.
 */

static int mx_add_user(char* login, char* password, char* nickname) {
    sqlite3 *db = opening_db();

    char *message_error;
    char sql[400];
    bzero(sql, 400);
    sprintf(sql, "INSERT INTO USERS (LOGIN, PASSWORD, NICKNAME) VALUES('%s', '%s', '%s')", 
    login, password, nickname);

    int exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    mx_db_msg_error(exit, message_error);

    sqlite3_close(db);
    return 0;
}

void def_database() {
    sqlite3 *db = opening_db();
    int exit;
    char *message_error;
    char *sql;

    sqlite3_close(db);
}
