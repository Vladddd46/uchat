#include "server.h"

static char* mx_stringcopy(const unsigned char* copy) {
    int len = mx_strlen((char*)copy);
    char* str = mx_strnew(len);

    for(int i = 0; i < len; i++)
        *(str + i) = *(copy + i);
    return str;
}

static void dberror(sqlite3 *db, int status, char *msg) {
    if (status != SQLITE_OK) {
        write(2, msg, (int)strlen(msg));
        write(2, "\n", 1);
        sqlite3_close(db); 
        exit(1);
    }
}

chats_t* mx_get_users_chats(char* user) {
	sqlite3 *db;
    char sql[120];
    sqlite3_stmt *res;
    sqlite3_stmt *res1;
    const unsigned char* user_id;
    chats_t *chat = malloc(sizeof(chats_t));
    chats_t *head = chat;
    int user_chat[1024];
    int len = 0;
    const unsigned char* identifier;
    sqlite3_stmt *res2;

    sqlite3_open("uchat.db", &db);
    sprintf(sql, "SELECT ID FROM USERS WHERE LOGIN='%s';", user);
    int check = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    dberror(db, check, "Error select ID from LOGIN");
    sqlite3_step(res);
    user_id = sqlite3_column_text(res, 0);
    sprintf(sql, "SELECT CHATID FROM USERCHAT WHERE USERID=%s;", user_id);
    check = sqlite3_prepare_v2(db, sql, -1, &res1, 0);
    dberror(db, check, "Error select CHATID from USERCHAT");
    sqlite3_step(res1);
    for(; sqlite3_column_text(res1, 0) != NULL; len++) {
        identifier = sqlite3_column_text(res1, 0);
        sprintf(sql, "SELECT CHATNAME, LASTMESSAGE FROM CHATS WHERE ID=%s;", identifier);
        check = sqlite3_prepare_v2(db, sql, -1, &res2, 0);
        dberror(db, check, "Error select CHATNAME, LASTMESSAGE from CHATs");
        sqlite3_step(res2);
        chat -> chat_name = mx_stringcopy(sqlite3_column_text(res2, 0));
        chat -> last_message = mx_stringcopy(sqlite3_column_text(res2, 1));
        chat -> next = malloc(sizeof(chats_t));
        chat = chat -> next;
        chat -> chat_name = NULL;
        chat -> last_message = NULL;
        chat -> next = NULL;   // 0442048098 Татьяна Валентиновна
        sqlite3_step(res1);
        sqlite3_finalize(res2);
    }
    sqlite3_finalize(res);
    sqlite3_finalize(res1);
    sqlite3_close(db);
    return head;
}











