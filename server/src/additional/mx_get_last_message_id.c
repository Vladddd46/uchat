#include "server.h"

static void db_null_error() {
    char *msg = "mx_get_last_message_id| Request to db returned NULL\n";

    write(2, msg, (int)strlen(msg));
    exit(1);
}

// Gets last msg id from chat with chat_id.
int mx_get_last_message_id(int chat_id) {
    sqlite3 *db = opening_db();
    sqlite3_stmt *res;
    char sql[200];
    bzero(sql, 200);
    int last_message_id = 0;
    char *last_message_id_str = NULL;

    sprintf(sql, "SELECT MAX(MESSAGEID) FROM MESSAGES WHERE CHATID='%d';", chat_id);
    int exit = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    dberror(db, exit, "mx_get_last_message_id | SELECT error");
    sqlite3_step(res);
    if((sqlite3_column_text(res, 0)) != NULL) {
        last_message_id_str = (char *)sqlite3_column_text(res, 0);
        if (last_message_id_str == NULL)
            db_null_error();
        last_message_id = atoi(last_message_id_str);
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
    return last_message_id;
}
