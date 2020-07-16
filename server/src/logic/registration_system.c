#include "server.h"

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
    if (sqlite3_column_text(res, 0) != NULL) {
        sqlite3_finalize(res);
        sqlite3_close(db);
        return "STATUS:login exist";
    }
    else {
        sprintf(sql, "SELECT PASSWORD FROM USERS WHERE NICKNAME='%s';", nickname);
        check = sqlite3_prepare_v2(db, sql, -1, &res1, 0);
        sqlite3_step(res1);
        if (sqlite3_column_text(res1, 0) != NULL) {
            sqlite3_finalize(res1);
            sqlite3_finalize(res);
            sqlite3_close(db);
            return "STATUS:nickname exist";
        }
        else {
            sprintf(sql, "INSERT INTO USERS (LOGIN, NICKNAME, PASSWORD) VALUES('%s', '%s', '%s');", login, nickname, password);
            check = sqlite3_exec(db, sql, NULL, 0, &message_error);
            sqlite3_finalize(res1);
            sqlite3_finalize(res);
            sqlite3_close(db);
            return "STATUS:success";
        }
    }
}

char *registration_system(char *packet) {
    char *login    = get_value_by_key(packet, "LOGIN");
    char *password = get_value_by_key(packet, "PASSWORD");
    char *nickname = get_value_by_key(packet, "NICKNAME");
    char *return_status   = mx_add_user(login, password, nickname);
    char *to = mx_strjoin("TO:", login);
    char *sendback_packet = json_packet_former(3, "TYPE:reg_s", return_status, to); // Debug.
    
    printf("Packet to client %s", sendback_packet);
    return sendback_packet;
}
