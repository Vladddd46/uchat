#include "server.h"

static int mx_get_user_id(char* login) {
    int user_id = 0;
    char sql[150];
    bzero(sql, 150);
    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *res;
    
    sprintf(sql, "SELECT ID FROM USERS WHERE LOGIN='%s'", login);
    int check = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    mx_dberror(db, check, "SELECT ID FROM USERS WHERE LOGIN");
    sqlite3_step(res);
    user_id = atoi(mx_string_copy((char*)sqlite3_column_text(res, 0)));
    sqlite3_finalize(res);
    sqlite3_close(db);
    return user_id;
}



static bool mx_check_contact_exits(char* mylogin, char *login) {
    bool status = false;
    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *res;
    sqlite3_stmt *res1;
    char *sql = "SELECT CHATNAME FROM CHATS";

    int check = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    mx_dberror(db, check, "SELECT CHATNAME FROM CHATS");
    sqlite3_step(res);

    while(sqlite3_column_text(res, 0) != NULL && status == false) {
        if(strstr((const char*)sqlite3_column_text(res, 0), mylogin) != NULL 
        && strstr((const char*)sqlite3_column_text(res, 0), login) != NULL) {
            status = true;
        }
        sqlite3_step(res);
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
    return status;
}



static int mx_get_last_chat_id() {
    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *res;
    char sql[100];
    bzero(sql, 100);
    int last_chat_id = 0;
    
    sprintf(sql, "SELECT MAX(CHATID) FROM USERCHAT;");
    int check = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    mx_dberror(db, check, "SELECT MAX(CHATID) FROM USERCHAT");
    sqlite3_step(res); 
    if(sqlite3_column_text(res, 0) != NULL)
        last_chat_id = atoi(mx_string_copy((char*)sqlite3_column_text(res, 0)));
    sqlite3_finalize(res);
    sqlite3_close(db);
    return last_chat_id;
}



static int mx_get_amount_of_chats(int user_id) {
    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *res;
    char sql[100];
    bzero(sql, 100);
    int counter = -1;
    
    int last_chat_id = 0;
    
    sprintf(sql, "SELECT CHATID FROM USERCHAT WHERE USERID = %d;", user_id);
    int check = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    mx_dberror(db, check, "SELECT CHATID FROM USERCHAT WHERE USERID");
    sqlite3_step(res); 
    while(sqlite3_column_text(res, 0) != NULL) {
        counter++;
        sqlite3_step(res);
    }
    sqlite3_finalize(res);
    sqlite3_close(db);
    return counter;
}



static char *json_packet_former_from_list(chats_t *chat, char *status, char* login, char* mylogin) {
    int list_len = mx_chats_list_len(chat);
    cJSON *packet = cJSON_CreateObject();
    char* packet_str = NULL;
    cJSON *json_value = cJSON_CreateString("add_new_user_s");
    char *nickname = mx_get_nickname_by_login(login);
    char to_users[100];
    
    bzero(to_users, 100);
    sprintf(to_users, "%s %s", login, mylogin);
    cJSON_AddItemToObject(packet, "TYPE", json_value);
    json_value = cJSON_CreateString(status);
    cJSON_AddItemToObject(packet, "STATUS", json_value);
    json_value =  cJSON_CreateString(to_users);
    cJSON_AddItemToObject(packet, "TO", json_value);
    json_value =  cJSON_CreateString("1");
    cJSON_AddItemToObject(packet, "LENGTH", json_value);
    char chat_name_former[100];
    bzero(chat_name_former, 100);
    sprintf(chat_name_former, "CHATNAME=%d", mx_get_amount_of_chats(mx_get_user_id(login)));
    json_value = cJSON_CreateString(to_users);
    cJSON_AddItemToObject(packet, chat_name_former, json_value);
    sprintf(chat_name_former, "CHATNAME=%d", mx_get_amount_of_chats(mx_get_user_id(mylogin)));
    json_value = cJSON_CreateString(to_users);
    cJSON_AddItemToObject(packet, chat_name_former, json_value);
    json_value = cJSON_CreateString("chat created");
    sprintf(chat_name_former, "LASTMESSAGE=%d", mx_get_amount_of_chats(mx_get_user_id(login)));
    cJSON_AddItemToObject(packet, chat_name_former, json_value);
    json_value = cJSON_CreateString("chat created");
    sprintf(chat_name_former, "LASTMESSAGE=%d", mx_get_amount_of_chats(mx_get_user_id(mylogin)));
    cJSON_AddItemToObject(packet, chat_name_former, json_value);
    json_value = cJSON_CreateString(mx_itoa(mx_get_last_chat_id()));
    sprintf(chat_name_former, "CHATID=%d", mx_get_amount_of_chats(mx_get_user_id(login))); 
    cJSON_AddItemToObject(packet, chat_name_former, json_value);
    json_value = cJSON_CreateString(mx_itoa(mx_get_last_chat_id()));
    sprintf(chat_name_former, "CHATID=%d", mx_get_amount_of_chats(mx_get_user_id(mylogin)));
    cJSON_AddItemToObject(packet, chat_name_former, json_value);
    chat = chat -> next;
    packet_str = cJSON_Print(packet);
    free(nickname);
    return packet_str;
}

static char *mx_add_contact_success(char *message_error, char *login, char *mylogin, sqlite3 *db) {
    char *sendback_packet;
    int mylogin_id = mx_get_user_id(mylogin);
    int login_id = mx_get_user_id(login);
    if(mylogin_id == login_id) return NULL;
    char sql[200];
    bzero(sql, 200);
    int last_chat_id = mx_get_last_chat_id();
    sprintf(sql, "INSERT INTO USERCHAT(USERID, CHATID) VALUES(%d, %d);", mylogin_id, last_chat_id + 1);
    int check = sqlite3_exec(db, sql, NULL, 0, &message_error);
    mx_dberror(db, check, "INSERT INTO USERCHAT(USERID, CHATID) VALUES 1");
    sprintf(sql, "INSERT INTO USERCHAT(USERID, CHATID) VALUES(%d, %d);", login_id, last_chat_id + 1);
    check = sqlite3_exec(db, sql, NULL, 0, &message_error);
    mx_dberror(db, check, "INSERT INTO USERCHAT(USERID, CHATID) VALUES 2");
    sprintf(sql, "INSERT INTO CHATS(CHATNAME, LASTMESSAGE) VALUES('%s %s', 'created chat');", login, mylogin);
    check = sqlite3_exec(db, sql, NULL, 0, &message_error);
    mx_dberror(db, check, "INSERT INTO CHATS(CHATNAME, LASMESSAGE) VALUES");
    sprintf(sql, "INSERT INTO MESSAGES(CHATID, MSGTYPE, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(%d, 'string', 1, '%s', 'null', 'chat created');", last_chat_id + 1, mylogin);
    check = sqlite3_exec(db, sql, NULL, 0, &message_error);
    mx_dberror(db, check, "INSERT INTO MESSAGES(CHATID, MESSAGEID, SENDER, TIME, MESSAGE)");
    chats_t *chat = mx_get_users_chats(mylogin);
    sendback_packet = json_packet_former_from_list(chat, "success", mylogin, login);
    return sendback_packet;
}

char *mx_add_contact(char *packet) {
    char *login = get_value_by_key(packet, "USER");
    char *mylogin = get_value_by_key(packet, "TO");
    char *sendback_packet;
    char *message_error = NULL;
    sqlite3 *db = mx_opening_db();

    if(!mx_check_contact_exits(mylogin, login))
        sendback_packet = mx_add_contact_success(message_error, login, mylogin, db);
    else {
        chats_t *chat   = mx_get_users_chats(mylogin);
        sendback_packet = json_packet_former_from_list(chat, "false", mylogin, login);
    }
    sqlite3_close(db);
    return sendback_packet;
}
