#include "server.h"

/*
 * Returns list of chats, where user
 * with(user_id) is the member.
 */

static void malloc_error_checker(chats_t *chat) {
    char *msg;

    if (chat == NULL) {
        msg =  "Malloc error\n";
        write(2, msg, (int)strlen(msg));
        exit(1);
    }
}

static char *get_user_id_by_login(char *login) {
    sqlite3 *db = opening_db();
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
    sqlite3_close(db);
    return user_id;
}

static chats_t *create_chats_node(char *chat_name, char *last_message) {
    chats_t *chat = (chats_t *)malloc(sizeof(chats_t));
    malloc_error_checker(chat);
    chat->chat_name    = chat_name;
    chat->last_message = last_message;
    chat->next = NULL;
    return chat; 
}

static void push_chats_front(chats_t **chats, char *chat_name, char *last_message) {
    chats_t *chat = create_chats_node(chat_name, last_message);
    chats_t *tmp;

    if (*chats == NULL)
        *chats = chat;
    else {
        tmp = *chats;
        while(tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = chat;
    }
}

chats_t *mx_get_users_chats(char *user) {
    sqlite3_stmt *res;
    char *identifier = NULL;
    chats_t *chat = NULL;
    sqlite3_stmt *res2;
    char sql[200];
    bzero(sql, 200);
    char* message_error = NULL;
    
    
    char *user_id = get_user_id_by_login(user);

    sqlite3 *db = opening_db();

    sprintf(sql, "SELECT CHATID FROM USERCHAT WHERE USERID=%s;", user_id);
    int check = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    dberror(db, check, "Error select CHATID from USERCHAT");
    sqlite3_step(res);
    
    while(sqlite3_column_text(res, 0) != NULL) {
        identifier = (char *)sqlite3_column_text(res, 0);
        sprintf(sql, "SELECT CHATNAME, LASTMESSAGE FROM CHATS WHERE ID=%s;", identifier);
        check = sqlite3_prepare_v2(db, sql, -1, &res2, 0);
        dberror(db, check, "Error select CHATNAME, LASTMESSAGE from CHATs");
        sqlite3_step(res2);
        char *chat_name    = mx_string_copy((char *)sqlite3_column_text(res2, 0));
        char *last_message = mx_string_copy((char *)sqlite3_column_text(res2, 1));
        push_chats_front(&chat, chat_name, last_message);
        sqlite3_step(res);
        sqlite3_finalize(res2);
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
    free(user_id);
    return chat;
}











