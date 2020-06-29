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

static char* mx_stringcopy(char* copy) {
    int len = mx_strlen(copy);
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

// static int mx_callback(void* not_used, int argc, char** argv, char** az_con_name) {
//     for(int i = 0; i < argc; i++) {
//         printf("%s: %s\n", az_con_name[i], argv[i]);
//     }
//     return 0;
// }

// static int mx_get_data(const char* str) {
//     sqlite3 *db;
//     int exit = sqlite3_open(str, &db);
//     printf("from\n");
//     char* sql = "SELECT * FROM USERS;";
//     sqlite3_exec(db, sql, mx_callback, NULL, NULL);
//     printf("end\n");
//     return 0;
// }

chats_t* mx_get_users_chats(char* user) {
	sqlite3 *db;
	sqlite3_open("uchat.db", &db);
    char* sql = "SELECT ID FROM USERS WHERE USER=";
    sqlite3_stmt *res;
    sqlite3_stmt *res1;
    int user_id;
    chats_t *chat = malloc(sizeof(chats_t*));
    chats_t *head = chat;
    int user_chat[1024];
    int len = 0;
    char* identifier;

    // mx_get_data("uchat.db");

    user = mx_pack_string_in_double_dots(user);
    sql = mx_strjoin(sql, user);
    sql = mx_strjoin(sql, ";");
    int check = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    // dberror(db, check, "Can't find this user");
    sqlite3_step(res);
    user_id = (int)sqlite3_column_text(res, 0);
    sql = mx_strjoin("SELECT CHATID FROM USERCHAT WHERE USERID=", mx_itoa(user_id));
    sql = mx_strjoin(sql, ";");
    sqlite3_prepare_v2(db, sql, -1, &res1, 0);
    sqlite3_step(res1);
    for(; sqlite3_column_text(res1, 0) != NULL; len++) {
        sqlite3_stmt *res2;
        identifier = sqlite3_column_text(res1, 0);
        sql = mx_strjoin("SELECT CHATNAME, LASTMESSAGE FROM CHATS WHERE ID=", identifier);
        sql = mx_strjoin(sql, ";");
        sqlite3_prepare_v2(db, sql, -1, &res2, 0);
        sqlite3_step(res1);
        sqlite3_step(res2);

        chat -> chat_name = sqlite3_column_text(res2, 0); 
        chat -> last_message = sqlite3_column_text(res2, 1);
        chat -> next = malloc(sizeof(chats_t*));
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
    chat = head;
    // printf("table for %s\n", user);
    // while(chat -> chat_name != NULL) {
    //     printf("chatname: %s\nlast message: %s\n\n", chat -> chat_name, chat -> last_message);
    //     chat = chat -> next;
    // }
    return head;
}











