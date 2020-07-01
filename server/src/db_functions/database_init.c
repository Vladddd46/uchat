#include "server.h"

/*
 * Initialize database, if it does not exist.
 * Creates user(login = admin, password = qwerty) by default.
 */

static char* mx_insert_all_args(char *login, char *password, char *nickname) {
    char* request = mx_strjoin("INSERT INTO USERS (LOGIN, PASSWORD, NICKNAME) VALUES('", login);

    request = mx_strjoin(request, "', '");
    request = mx_strjoin(request, password);
    request = mx_strjoin(request, "', '");
    request = mx_strjoin(request, nickname);
    request = mx_strjoin(request, "');");
    // printf("%s", request);
    return request;
}

static int mx_add_user(char* login, char* password, char* nickname) {
    sqlite3 *db;
    char *message_error;
    int exit = sqlite3_open("uchat.db", &db);
    char* sql = mx_insert_all_args(login, password, nickname);

    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    if(exit != SQLITE_OK) {
        printf("Error inserting User");
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
        "ID       INTEGER PRIMARY KEY AUTOINCREMENT, "
        "LOGIN    TEXT NOT NULL, "
        "PASSWORD TEXT NOT NULL, "
        "NICKNAME TEXT NOT NULL);";

    exit = sqlite3_open("uchat.db", &db);
    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    dberror(db, exit, "Error to create USERS table");
    sql = "CREATE TABLE IF NOT EXISTS CHATS("
        "ID          INTEGER PRIMARY KEY AUTOINCREMENT, "
        "CHATNAME    TEXT NOT NULL, " // тут должна быть какая-то шняга Влада
        "LASTMESSAGE TEXT NOT NULL);";
    exit = sqlite3_open("uchat.db", &db);
    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    dberror(db, exit, "Error to create CHATS table");

    sql = "CREATE TABLE IF NOT EXISTS USERCHAT("
        "USERID     INTEGER NOT NULL, "
        "CHATID     INTEGER NOT NULL);";
    exit = sqlite3_open("uchat.db", &db);
    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    dberror(db, exit, "Тут проблема 1");

    sql = "CREATE TABLE IF NOT EXISTS MESSAGES("
        "CHATID     INTEGER, " 
        "SENDER     TEXT NOT NULL, "
        "TIME       TEXT NOT NULL, "
        "MESSAGE    TEXT NOT NULL);";
    exit = sqlite3_open("uchat.db", &db);
    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);

    /* добавление тестовых даных в БД */
    mx_add_user("Yura", "1234", "jorsh");
    mx_add_user("Vlad", "qwerty", "vdepesh");
    dberror(db, exit, "Error to create MESSAGES table");

    sql = "INSERT INTO CHATS (CHATNAME, LASTMESSAGE) VALUES('YuraVlad', 'hello');";
    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    dberror(db, exit, "Error inserting to Chats table");

        // sql = "SELECT CHATNAME, LASTMESSAGE FROM CHATS WHERE ID=1;";
        // printf("SQL string: %s\n", sql);
        // sqlite3_stmt *res2;
        // int check = sqlite3_prepare_v2(db, sql, -1, &res2, 0);
        // dberror(db, check, "Error select CHATNAME, LASTMESSAGE from CHATs");
        // sqlite3_step(res2);

        // printf("%s", sqlite3_column_text(res2, 0));


    sql = "INSERT INTO USERCHAT (USERID, CHATID) VALUES(1, 1);";
    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    dberror(db, exit, "Error inserting to UserChats table");
    sql = "INSERT INTO USERCHAT (USERID, CHATID) VALUES(2, 1);";
    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    dberror(db, exit, "Error inserting to UserChats table");

    /*-----------------------------------------------------*/
    sqlite3_close(db);
}
