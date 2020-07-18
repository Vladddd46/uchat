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
    printf("%s\n", login);
    sprintf(sql, "SELECT ID FROM USERS WHERE LOGIN='%s';", login);
    check = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    printf("%s\n", sql);
    dberror(db, check, "Error select ID from LOGIN");
    sqlite3_step(res);
    printf("4\n");
    char *resx = (char *)sqlite3_column_text(res, 0);
    printf(">>%s\n", resx);
    user_id = mx_string_copy(resx);
    printf("3\n");
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

static char** mx_get_users_chat_id(char* user_id) {
    char sql[200];
    bzero(sql, 200);
    char* message_error = NULL;
    sqlite3 *db = opening_db();
    char** chat_id_arr = mx_new_strarr(2000);
    int arr_index = 0;
    sqlite3_stmt *res;

    sprintf(sql, "SELECT CHATID FROM USERCHAT WHERE USERID=%s;", user_id);
    int check = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    dberror(db, check, "Error select CHATID from USERCHAT");
    sqlite3_step(res);
    
    while(sqlite3_column_text(res, 0) != NULL) {
        *(chat_id_arr + arr_index) = mx_string_copy((char *)sqlite3_column_text(res, 0));
        printf("%s\n", mx_string_copy((char *)sqlite3_column_text(res, 0)));
        arr_index++;
        sqlite3_step(res);
    }
    *(chat_id_arr + arr_index) = NULL;
    sqlite3_finalize(res);
    sqlite3_close(db);
    return chat_id_arr;
}

chats_t *mx_get_users_chats(char *user) {
    sqlite3_stmt *res;
    chats_t *chat = NULL;
    char sql[200];
    bzero(sql, 200);
    char* message_error = NULL;
    char *user_id = get_user_id_by_login(user);

    char** chats_arr = mx_get_users_chat_id(user_id);
    int arr_index = 0;

    
    sqlite3 *db = opening_db();

    while(*(chats_arr + arr_index) != NULL) {
        sprintf(sql, "SELECT CHATNAME, LASTMESSAGE FROM CHATS WHERE ID=%s;", *(chats_arr + arr_index));
        int check = sqlite3_prepare_v2(db, sql, -1, &res, 0);
        dberror(db, check, "Error select CHATNAME, LASTMESSAGE from CHATs");
        sqlite3_step(res);
        char *chat_name    = mx_string_copy((char *)sqlite3_column_text(res, 0));
        char *last_message = mx_string_copy((char *)sqlite3_column_text(res, 1));
        push_chats_front(&chat, chat_name, last_message);
        sqlite3_finalize(res);
        arr_index++;
    }

    sqlite3_close(db);
    free(user_id);
    return chat;
}











