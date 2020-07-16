#include "server.h"

static char* mx_pack_string_in_double_dots(char* str) {
    char *new_str = mx_strnew(mx_strlen(str) + 2);
    int i = 0;

    *(new_str) = 34;
    for(; i < mx_strlen(str); i++)
    	*(new_str + i + 1) = *(str + i);
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

static char* mx_stringcopy(const unsigned char* copy) {
    int len = mx_strlen((char*)copy);
    char* str = mx_strnew(len);

    for(int i = 0; i < len; i++)
        *(str + i) = *(copy + i);
    return str;
}

static void malloc_error_checker(chats_t *chat) {
    char *msg;

    if (chat == NULL) {
        msg =  "Malloc error\n";
        write(2, msg, (int)strlen(msg));
        exit(1);
    }
}

static char *get_user_id_by_login(sqlite3 *db, char *login) {
    char sql[200];
    bzero(sql, 200);
    sqlite3_stmt *res;
    int check;
    char *user_id;

    sprintf(sql, "SELECT ID FROM USERS WHERE LOGIN='%s';", login);
    check = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    dberror(db, check, "Error select ID from LOGIN");
    sqlite3_step(res);
    user_id = mx_string_copy((char *)sqlite3_column_text(res, 0));

    sqlite3_finalize(res);
    return user_id;
}

chats_t *mx_get_users_chats(char *user) {
	sqlite3 *db = opening_db();
    char sql[200];
    bzero(sql, 200);

    sqlite3_stmt *res1;
    const unsigned char *identifier;

    chats_t *chat = (chats_t *)malloc(sizeof(chats_t));
    malloc_error_checker(chat);

    chats_t *head = chat;
    int user_chat[1024];
    int len = 0;
    sqlite3_stmt *res2;

    char *user_id = get_user_id_by_login(db, user);


    sprintf(sql, "SELECT CHATID FROM USERCHAT WHERE USERID=%s;", user_id);
    int check = sqlite3_prepare_v2(db, sql, -1, &res1, 0);
    dberror(db, check, "Error select CHATID from USERCHAT");
    sqlite3_step(res1);
    for(; sqlite3_column_text(res1, 0) != NULL; len++) {
        identifier = sqlite3_column_text(res1, 0);
        sprintf(sql, "SELECT CHATNAME, LASTMESSAGE FROM CHATS WHERE ID=%s;", identifier);
        check = sqlite3_prepare_v2(db, sql, -1, &res2, 0);
        dberror(db, check, "Error select CHATNAME, LASTMESSAGE from CHATs");
        sqlite3_step(res2);
        chat -> chat_name = mx_string_copy((char *)sqlite3_column_text(res2, 0));
        chat -> last_message = mx_string_copy((char *)sqlite3_column_text(res2, 1));
        chat -> next = malloc(sizeof(chats_t));
        chat = chat -> next;
        chat -> chat_name = NULL;
        chat -> last_message = NULL;
        chat -> next = NULL;   // 0442048098 Татьяна Валентиновна
        sqlite3_step(res1);
        sqlite3_finalize(res2);
    }

    sqlite3_finalize(res1);
    sqlite3_close(db);
    free(user_id);
    return head;
}











