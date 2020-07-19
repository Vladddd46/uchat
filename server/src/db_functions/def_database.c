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
    sprintf(sql, "INSERT INTO USERS (LOGIN, PASSWORD, NICKNAME) VALUES('%s', '%s', '%s')", login, password, nickname);

    int exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    db_msg_error(exit, message_error);

    sqlite3_close(db);
    return 0;
}

void def_database() {
    sqlite3 *db = opening_db();
    int exit;
    char *message_error;
    char *sql;

    /* добавление тестовых даных в БД */
    mx_add_user("Yura", "1234", "jorsh");
    mx_add_user("Vlad", "qwerty", "vdepesh");
    mx_add_user("Denis", "1234", "den");

    // sql = "INSERT INTO CHATS (CHATNAME, LASTMESSAGE) VALUES('Yura Vlad', 'hello');";
    // exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    // dberror(db, exit, "Error inserting to Chats table");

    // /* добавляем сообщения в чат */
    // sql = "INSERT INTO MESSAGES (CHATID, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(1, 1, 'Yura', '12:42', 'Hello');";
    // exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    // sql = "INSERT INTO MESSAGES (CHATID, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(1, 2, 'Vlad', '12:42','Hi');";
    // exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    // sql = "INSERT INTO MESSAGES (CHATID, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(1, 3, 'Yura', '12:42','How are you?');";
    // exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    // sql = "INSERT INTO MESSAGES (CHATID, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(1, 4, 'Vlad', '12:42','Im fine');";
    // exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    // sql = "INSERT INTO MESSAGES (CHATID, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(1, 5, 'Vlad', '12:43','And you?');";
    // exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    // sql = "INSERT INTO MESSAGES (CHATID, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(1, 6, 'Yura', '12:43','Im okay');";
    // exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    // sql = "INSERT INTO MESSAGES (CHATID, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(1, 7, 'Yura', '12:43','How do you fell to play golf?');";
    // exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    // sql = "INSERT INTO MESSAGES (CHATID, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(1, 8, 'Vlad', '12:44','Its going to be rain today');";
    // exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    // sql = "INSERT INTO MESSAGES (CHATID, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(1, 9, 'Vlad', '12:44','I think we can play on Saturday');";
    // exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    // sql = "INSERT INTO MESSAGES (CHATID, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(1, 10, 'Yura', '12:44','Nice');";
    // exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    // sql = "INSERT INTO MESSAGES (CHATID, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(1, 11, 'Yura', '12:45','Where will we meet?');";
    // exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    // sql = "INSERT INTO MESSAGES (CHATID, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(1, 12, 'Vlad', '12:45','I think near Unit City!');";
    // exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    // sql = "INSERT INTO MESSAGES (CHATID, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(1, 13, 'Yura', '12:45','Well, i wiil see you there');";
    // exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    // sql = "INSERT INTO MESSAGES (CHATID, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(1, 14, 'Yura', '12:46','bye');";
    // exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    // sql = "INSERT INTO MESSAGES (CHATID, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(1, 15, 'Vlad', '12:46','good bye');";
    // exit = sqlite3_exec(db, sql, NULL, 0, &message_error);


    // // sqlite3_busy_timeout(db, int 50000000);
    // dberror(db, exit, "Error inserting message to MESSAGES table");
    // /*-----------------------------------------------------*/
    // sql = "INSERT INTO USERCHAT (USERID, CHATID) VALUES(1, 1);";
    // exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    // dberror(db, exit, "Error inserting to UserChats table");
    // sql = "INSERT INTO USERCHAT (USERID, CHATID) VALUES(2, 1);";
    // exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    // dberror(db, exit, "Error inserting to UserChats table");
    /*-----------------------------------------------------*/

    sqlite3_close(db);
}
