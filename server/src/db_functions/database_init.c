#include "server.h"

/*
 * Initialize database, if it does not exist.
 * Creates user(login = admin, password = qwerty) by default.
 */

static char* mx_insert_all_args(char* login, char* password, char* nickname) {
    char* request = mx_strjoin("INSERT INTO USERS (LOGIN, PASSWORD, NICKNAME) VALUES('", login);

    request = mx_strjoin(request, "', '");
    request = mx_strjoin(request, password);
    request = mx_strjoin(request, "');");
    // printf("%s", request);
    return request;
}

static int mx_add_user(const char *str, char* login, char* password, char* nickname) {
    sqlite3 *db;
    char *message_error;
    int exit = sqlite3_open(str, &db);
    char* sql = mx_insert_all_args(login, password, nickname);

    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    if(exit != SQLITE_OK) {
        printf("Error insert");
        sqlite3_free(message_error);
    }
    return 0;
}

static void dberror(sqlite3 *db, int status, char *msg) {
    if (status != SQLITE_OK) {
        write(2, msg, (int)strlen(msg));
        write(2, "\n", 1);
        sqlite3_close(db); 
        exit(1);
    }
}

void database_init() {
    sqlite3* db;
    int exit = 0;
    char *message_error;
    char *sql = "CREATE TABLE IF NOT EXISTS USERS("
        "ID     INTEGER PRIMARY KEY AUTOINCREMENT, "
        "LOGIN  TEXT NOT NULL, "
        "NICKNAME TEXT NOT NULL, "
        "PASSWORD TEXT NOT NULL);";
    mx_add_user("uchat.db", "admin", "qwerty", "admin");

    exit = sqlite3_open("uchat.db", &db);
    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);

    if(exit != SQLITE_OK) {
        printf("Error to create a table ");
    }
    sql = "CREATE TABLE IF NOT EXISTS MESSAGES("
        "USER TEXT NOT NULL, "
        "SENDER TEXT NOT NULL, "
        "TIME TEXT NOT NULL, "
        "MESSAGE TEXT NOT NULL);";
    exit = sqlite3_open("uchat.db", &db);
    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);

    dberror(db, exit, "Error");
    sqlite3_close(db);
}
