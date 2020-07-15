#include "server.h"

static int mx_get_user_id(char* login) {
	int user_id = 0;
    char sql[150];
    sqlite3 *db;
	sqlite3_stmt *res;
    
    sqlite3_open("uchat.db", &db);
    sprintf(sql, "SELECT ID FROM USERS WHERE LOGIN='%s'", login);
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    user_id = atoi(mx_string_copy((char*)sqlite3_column_text(res, 0)));
    return user_id;
}

// static char* mx_get_special_chat_name(char* chat_name, char* login) {
//     char* result = 
//     return result;
// }

static bool mx_check_contact_exits(char* mylogin, char* login) {
	bool status = false;
	sqlite3 *db;
	sqlite3_stmt *res;
	sqlite3_stmt *res1;
	char sql[200];

    sqlite3_open("uchat.db", &db);
    sprintf(sql, "SELECT ID FROM CHATS WHERE CHATNAME='%s'", mx_strjoin(mylogin, login));
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    if(sqlite3_column_text(res, 0) != NULL) {
    	status = true;
    }
    sprintf(sql, "SELECT ID FROM CHATS WHERE CHATNAME='%s'", mx_strjoin(login, mylogin));
    sqlite3_prepare_v2(db, sql, -1, &res1, 0);
    sqlite3_step(res1);
    if(sqlite3_column_text(res1, 0) != NULL) {
    	status = true;
    }
    return status;
}

static char* mx_get_nickname(char* login) {
    sqlite3 *db = NULL;
    char sql[200];
    sprintf(sql, "SELECT NICKNAME FROM USERS WHERE LOGIN='%s';", login);
    sqlite3_stmt *res;
    char* nickname;

    sqlite3_open("uchat.db", &db);
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    nickname = (char*)sqlite3_column_text(res, 0);
    return nickname;
}

static int mx_list_len(chats_t* chat) {
    int len = 0;
    chats_t* head = chat;

    while(chat -> chat_name != NULL) {
        chat = chat -> next;
        len++;
    }
    head = chat;
    return len;
}

static int mx_get_last_chat_id() {
	sqlite3 *db;
    sqlite3_stmt *res;
    char sql[100];
    int last_chat_id = 0;
    
    sqlite3_open("uchat.db", &db);
    sprintf(sql, "SELECT MAX(CHATID) FROM USERCHAT;");
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    sqlite3_step(res);
    last_chat_id = atoi(mx_string_copy((char*)sqlite3_column_text(res, 0)));
    return last_chat_id;
}

static char *json_packet_former_from_list(chats_t *chat, char *status, char* login, char* mylogin) {
    int list_len = mx_list_len(chat);
    cJSON *packet = cJSON_CreateObject();
    char* packet_str = NULL;
    cJSON *json_value = cJSON_CreateString("add_new_user_s");
    char *nickname = mx_get_nickname(login);

    cJSON_AddItemToObject(packet, "TYPE", json_value);
    json_value = cJSON_CreateString(status);
    cJSON_AddItemToObject(packet, "STATUS", json_value);
    json_value = cJSON_CreateString(nickname);
    cJSON_AddItemToObject(packet, "NICKNAME", json_value);
    json_value =  cJSON_CreateString(login);
    cJSON_AddItemToObject(packet, "TO", json_value);
    json_value =  cJSON_CreateString(mx_itoa(list_len));
    cJSON_AddItemToObject(packet, "LENGTH", json_value);
    for(int i = 0; i < list_len; i++) {
        char chat_name_former[100];

        sprintf(chat_name_former, "CHATNAME=%d", i);
        json_value = cJSON_CreateString(chat -> chat_name);
        cJSON_AddItemToObject(packet, chat_name_former, json_value);
        json_value = cJSON_CreateString(chat -> last_message);
        sprintf(chat_name_former, "LASTMESSAGE=%d", i);
        cJSON_AddItemToObject(packet, chat_name_former, json_value);
        chat = chat -> next;
    }
    packet_str = cJSON_Print(packet);
    return packet_str;
}

char* mx_add_contact(char* packet) {
	char* login = get_value_by_key(packet, "USER");
	char* mylogin = get_value_by_key(packet, "TO");
	chats_t *chat = mx_get_users_chats(mylogin);
	char* sendback_packet;
	char* message_error;
	sqlite3 *db;

	if(mx_check_contact_exits(mylogin, login)) {
        int mylogin_id = mx_get_user_id(mylogin);
	    int login_id = mx_get_user_id(login);
	    char sql[200];
	    int last_chat_id = mx_get_last_chat_id();

	    sqlite3_open("uchat.db", &db);
        sprintf(sql, "INSERT INTO USERCHAT(USERID, CHATID) VALUES(%d, %d);", mylogin_id, last_chat_id + 1);
        sqlite3_exec(db, sql, NULL, 0, &message_error);
        sprintf(sql, "INSERT INTO USERCHAT(USERID, CHATID) VALUES(%d, %d);", login_id, last_chat_id + 1);
        sqlite3_exec(db, sql, NULL, 0, &message_error);

        sprintf(sql, "INSERT INTO CHATS(CHATNAME, LASMESSAGE) VALUES('(%s %s)', ' ');", login, mylogin);
	    sendback_packet = json_packet_former_from_list(chat, "success", mylogin, login);
	}
	else
	    sendback_packet = json_packet_former_from_list(chat, "false", mylogin, login);
	return sendback_packet;
}