#include "db.h"

int mx_create_table(const char* str) {
    sqlite3* db;
    int exit = 0;
    char *message_error;
    char *sql = "CREATE TABLE IF NOT EXISTS USERS("
        "ID     INTEGER PRIMARY KEY AUTOINCREMENT, "
        "LOGIN	TEXT NOT NULL, "
        "PASSWORD TEXT NOT NULL);";

    exit = sqlite3_open(str, &db);
    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);

    if(exit != SQLITE_OK) {
    	printf("Error to create a table ");
    }
    sql = "CREATE TABLE IF NOT EXISTS MESSAGES("
        "USER TEXT NOT NULL, "
        "SENDER TEXT NOT NULL, "
        "TIME TEXT NOT NULL, "
        "MESSAGE TEXT NOT NULL);";
    exit = sqlite3_open(str, &db);
    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);

    if(exit != SQLITE_OK) {
        printf("Error to create a table ");
    }
    sqlite3_close(db);
    return 0;
}
