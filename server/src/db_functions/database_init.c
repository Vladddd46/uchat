#include "server.h"

// Initialize database, if it does not exist.
void mx_database_init() {
    sqlite3 *db = opening_db();
    int exit = 0;
    char *message_error;
    char *sql = "CREATE TABLE IF NOT EXISTS USERS("
        "ID       INTEGER PRIMARY KEY AUTOINCREMENT, "
        "LOGIN    TEXT NOT NULL, "
        "PASSWORD TEXT NOT NULL, "
        "NICKNAME TEXT NOT NULL);";
    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    mx_dberror(db, exit, "Error to create USERS table");
    sql = "CREATE TABLE IF NOT EXISTS CHATS("
        "ID          INTEGER PRIMARY KEY AUTOINCREMENT, "
        "CHATNAME    TEXT NOT NULL, "
        "LASTMESSAGE TEXT NOT NULL);";
    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    mx_dberror(db, exit, "Error to create CHATS table");

    sql = "CREATE TABLE IF NOT EXISTS USERCHAT("
        "USERID     INTEGER NOT NULL, "
        "CHATID     INTEGER NOT NULL);";
    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    mx_dberror(db, exit, "Тут проблема 1");

    sql = "CREATE TABLE IF NOT EXISTS MESSAGES("
        "CHATID     INTEGER, " 
        "MSGTYPE    TEXT NOT NULL, "
        "MESSAGEID  INTEGER, "
        "SENDER     TEXT NOT NULL, "
        "TIME       TEXT NOT NULL, "
        "MESSAGE    TEXT NOT NULL);";
    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    sqlite3_close(db);
}
