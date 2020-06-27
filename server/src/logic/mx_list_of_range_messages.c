#include "server.h"

static char* mx_stringcopy(char* copy) {
    int len = mx_strlen(copy);
    char* str = mx_strnew(len);

    for(int i = 0; i < len; i++)
        *(str + i) = *(copy + i);
    return str;
}

chat_message_t* mx_list_of_range_messages(int chat_id, int range_from, int range_to) {
    chat_message_t* list = malloc(sizeof(chat_message_t));
    chat_message_t* head = list;
    sqlite3 *db;
    sqlite3_stmt *res;
    char sql[200];

    sqlite3_open("uchat.db", &db);
    sprintf(sql, "%s%d", "SELECT SENDER, MESSAGE, TIME, FROM MESSAGES WHERE CHATID=", chat_id);
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);

    for(int i = 0; i < range_from && sqlite3_column_text(res, 0) != NULL; i++) {
    	sqlite3_step(res);
    }
    for(int i = range_from; i < range_to && sqlite3_column_text(res, 0) != NULL; i++) {
    	list -> sender = mx_stringcopy(sqlite3_column_text(res, 0));
    	list -> time = mx_stringcopy(sqlite3_column_text(res, 1));
    	list -> message = mx_stringcopy(sqlite3_column_text(res, 2));

        list -> next = malloc(sizeof(chat_message_t*));
        list = list -> next;
        list -> sender = NULL;
        list -> time = NULL;
        list -> message = NULL;
        sqlite3_step(res);
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
    return head;
}
