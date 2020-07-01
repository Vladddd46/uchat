#include "server.h"

/*
 * Initialize database, if it does not exist.
 * Creates user(login = admin, password = qwerty) by default.
 */

static void dberror(sqlite3 *db, int status, char *msg) {
    if (status != SQLITE_OK) {
        write(2, msg, (int)strlen(msg));
        write(2, "\n", 1);
        sqlite3_close(db); 
        exit(1);
    }
}

void database_init() {
    sqlite3 *db;
    int status = sqlite3_open("uchat.db", &db);
    dberror(db, status, "Can`t open database");

    char *sql = "CREATE TABLE IF NOT EXISTS Users(Id INT, Login TEXT, Password TEXT, Nickname TEXT);"
                "INSERT INTO Users VALUES(0, 'admin', 'qwerty', 'admin');";

    char *err_msg = 0;
    status = sqlite3_exec(db, sql, 0, 0, &err_msg);
    dberror(db, status, "Error");
    sqlite3_close(db);
}
