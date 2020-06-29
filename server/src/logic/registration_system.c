#include "server.h"

// static char *msg_former(int status) {
//     char *msg = NULL;

//     if (status == 1)
//         msg = "MSG:OK";
//     else if (status == 2)
//         msg = "MSG:User with such login is already exists";
//     else if (status == 3)
//         msg = "MSG:User with such nickname is already exists";
//     return msg;
// }

// static char *status_converter(int return_status) {
//     if (return_status == 1)
//         return "STATUS:true";
//     return "STATUS:false";
// }

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

static char* mx_login_available(const char* str, char* user) {
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


static char* mx_insert_all_args(char* login, char* password, char* nickname) {
	char* request = mx_strjoin("INSERT INTO USERS (LOGIN, NICKNAME, PASSWORD) VALUES('", login);

    request = mx_strjoin(request, "', '");
    request = mx_strjoin(request, nickname);
    request = mx_strjoin(request, "', '");
    request = mx_strjoin(request, password);
    request = mx_strjoin(request, "');");
    printf("%s", request);
    return request;
}

static int mx_add_user(const char *str, char* login, char* password, char* nickname) {
    sqlite3 *db;
    char *message_error;
    int exit = sqlite3_open(str, &db);
    char* sql = mx_insert_all_args(login, password, nickname);

    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    if(exit != SQLITE_OK)
    	sqlite3_free(message_error);
    return 1;
}
char *registration_system(char *packet) {
    char *login    = get_value_by_key(packet, "LOGIN");
    char *password = get_value_by_key(packet, "PASSWORD");
    char *nickname = get_value_by_key(packet, "NICKNAME");

    int  return_status     = mx_add_user("uchat.db", login, password, nickname);
    // char *status           = status_converter(return_status);
    // char *msg              = msg_former(return_status);

    // char *sendback_packet  = json_packet_former(2, "TYPE:reg_s", "STATUS:true", msg);
    char *sendback_packet = json_packet_former(3, "TYPE:reg_s", "STATUS:true", "MSG:OK"); // Debug.
    
    return sendback_packet;
}
