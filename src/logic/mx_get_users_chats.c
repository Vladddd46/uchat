#include "server.h"

static char* mx_pack_string_in_double_dots(char* str) {
    char *new_str = mx_strnew(mx_strlen(str) + 2);
    int i = 0;

    *(new_str) = 34;
    for(; i < mx_strlen(str); i++) {
    	*(new_str + i + 1) = *(str + i);
    }
    *(new_str + i + 1) = 34;
    return new_str;
}


static char** mx_add_to_arr(char** arr, char* str, int index) {
	*(arr + index) = mx_strnew(mx_strlen(str));

    for(int i = 0; i < mx_strlen(str); i++) {
    	*(*(arr + index) + i) = *(str + i);
    }
    return arr;
}

char* mx_get_users_last_message(const char* str, char* user) {
	sqlite3 *db;
    sqlite3_open(str, &db);
    char* sql = "SELECT MESSAGE, TIME FROM MESSAGES WHERE USER=";
    sqlite3_stmt *res;
    char* last_message;

    user = mx_pack_string_in_double_dots(user);
    sql = mx_strjoin(sql, user);
    sql = mx_strjoin(sql, ";");
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);

    while(sqlite3_column_text(res, 0) != NULL) {
        last_message = mx_strcpy(last_message, sqlite3_column_text(res, 0));
        sqlite3_step(res);
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
    return last_message;
}

chats_t* mx_get_users_chats(char* user) {
	sqlite3 *db;
	sqlite3_open("uchat.db", &db);
    char* sql = "SELECT ID FROM USERS WHERE USER=";
    sqlite3_stmt *res;
    int user_id;
    chats_t *chat;
    chats_t *head = chat;

    user = mx_pack_string_in_double_dots(user);
    sql = mx_strjoin(sql, user);
    sql = mx_strjoin(sql, ";");
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);

    user_id = (int)sqlite3_column_text(res, 0);
    sql = "SELECT CHATNAME, LASTMESSAGE FROM CHATS WHERE ID=";
    sql = mx_strjoin(sql, mx_itoa(user_id));
    sql = mx_strjoin(sql, ";");
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);

    // printf("\n\n\nUsers id = %d\n\n", user_id);
    while(sqlite3_column_text(res, 0) != NULL) {
        chat -> chat_name = sqlite3_column_text(res, 0);
        chat -> last_message = sqlite3_column_text(res, 1);
        chat -> next = malloc(sizeof(chats_t));
        chat = chat -> next;
        chat -> next = NULL;
        sqlite3_step(res);
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
    return chat;
}











