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

static char* mx_add_user(char* login, char* password, char* nickname) {
    sqlite3 *db;
    char *message_error;
    char sql[500];
    int check;
    sqlite3_stmt *res;
    sqlite3_stmt *res1;

    sqlite3_open("uchat.db", &db);
    sprintf(sql, "SELECT PASSWORD FROM USERS WHERE LOGIN='%s';", login);
    check = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    // printf("%s -- %s", sql, sqlite3_column_text(res, 0));
    if (sqlite3_column_text(res, 0) != NULL)
        return "MSG:login exist";
    else {
        sprintf(sql, "SELECT PASSWORD FROM USERS WHERE NICKNAME='%s';", nickname);
        check = sqlite3_prepare_v2(db, sql, -1, &res1, 0);
        // printf("%s", sqlite3_column_text(res, 0));
        sqlite3_step(res1);
        if (sqlite3_column_text(res1, 0) != NULL)
            return "MSG:nickname exist";
        else {
            sprintf(sql, "INSERT INTO USERS (LOGIN, NICKNAME, PASSWORD) VALUES('%s', '%s', '%s');", login, nickname, password);
            check = sqlite3_exec(db, sql, NULL, 0, &message_error);
            return "MSG:done";
        }
    }
}
char *registration_system(char *packet) {
    char *login    = get_value_by_key(packet, "LOGIN");
    char *password = get_value_by_key(packet, "PASSWORD");
    char *nickname = get_value_by_key(packet, "NICKNAME");
    char* return_status = mx_add_user(login, password, nickname);
    char *sendback_packet = json_packet_former(3, "TYPE:reg_s", "STATUS:true", return_status); // Debug.
    
    printf("Packet to client %s", sendback_packet);
    return sendback_packet;
}
