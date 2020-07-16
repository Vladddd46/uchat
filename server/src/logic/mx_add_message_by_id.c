#include "server.h"

static int mx_callback(void* not_used, int argc, char** argv, char** az_con_name) {
    for(int i = 0; i < argc; i++) {
        printf("%s: %s\n", az_con_name[i], argv[i]);
    }
    return 0;
}

static int mx_get_last_message_id(int chat_id) {
    sqlite3 *db = opening_db();
    sqlite3_stmt *res;
    char sql[100];
    int last_message_id = 0;

    sprintf(sql, "SELECT MAX(MESSAGEID) FROM MESSAGES WHERE CHATID='%d';", chat_id);
    int exit = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    dberror(db, exit, "Error inserting to table");
	sqlite3_step(res);
	if((sqlite3_column_text(res, 0)) != NULL)
        last_message_id = atoi((const char*)sqlite3_column_text(res, 0));
    sqlite3_finalize(res);
    sqlite3_close(db);
    return last_message_id;
}

static char* mx_delete_slesh_n(char *str) {
    *(str + mx_strlen(str) - 1) = '\0';
    return str; 
}

static void mx_add_last_message(int chat_id, char* message, char* time, char* sender) {
	sqlite3 *db = opening_db();
    char *message_error;
    char sql[1000];
    int check;
    int message_id = mx_get_last_message_id(chat_id);

    message_id++;
    // dberror(db, x, "Error to open");

    // char *login = NULL;
    // long long id = 8713645873465;

    // sqlite3_prepare_v2(db, "SELECT NICKNAME FROM USERS WHERE LOGIN = ?1 where id = ?2;", -1, &stmt, NULL);
    // sqlite3_bind_text(stmt, 1, text, -1, SQLITE_STATIC);
    // sqlite3_bind_int64(stmt, 2, id);
    // sqlite3_step(stmt);
                 // "INSERT INTO MESSAGES (CHATID, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(1, 1, 'Yura', '12:42', 'Hello');";
    sprintf(sql, "INSERT INTO MESSAGES (CHATID, MESSAGEID, SENDER, TIME, MESSAGE) VALUES(%d, %d, '%s', '%s', '%s');", chat_id, message_id, sender, mx_delete_slesh_n(time), mx_delete_slesh_n(message));
    printf("\n\nSQL req: %s\n\n", sql);
    check = sqlite3_exec(db, sql, NULL, 0, &message_error);

    dberror(db, check, "Error inserting to table");
    sqlite3_close(db);

    // char* sql1 = "SELECT * FROM MESSAGES WHERE CHATID=1";
    // sqlite3_exec(db, sql1, mx_callback, NULL, NULL);
}

static void mx_add_message_with_id(int message_id, int chat_id, char* message) {
	sqlite3 *db = opening_db();
    char *message_error;
    char sql[500];
    int check;

	sprintf(sql, "UPDATE MESSAGES SET MESSAGE = '%s' WHERE MESSAGEID = %d;", message ,message_id);
    check = sqlite3_exec(db, sql, NULL, 0, &message_error);
    sqlite3_close(db);
}

static char *mx_json_packet_former_from_list(char* message, char* time, char* sender, int chat_id, char* all_users) {
    cJSON *packet = cJSON_CreateObject();
    char* packet_str = NULL;
    cJSON *json_value = cJSON_CreateString("msg_s");

   // printf("\nLEN = %d\n", list_len);
    cJSON_AddItemToObject(packet, "TYPE", json_value);
    json_value = cJSON_CreateString(all_users);
    cJSON_AddItemToObject(packet, "TO", json_value);
    char packet_former[100];
    sprintf(packet_former, "ID0");
    json_value = cJSON_CreateString(mx_itoa(mx_get_last_message_id(chat_id)));
    cJSON_AddItemToObject(packet, packet_former, json_value);
    json_value = cJSON_CreateString("0");
    cJSON_AddItemToObject(packet, "MSGLEN", json_value);
    json_value = cJSON_CreateString(all_users);
    cJSON_AddItemToObject(packet, "ALLUSERS", json_value);
    json_value = cJSON_CreateString(sender);
    sprintf(packet_former, "SENDER0");
    cJSON_AddItemToObject(packet, packet_former, json_value);
    json_value = cJSON_CreateString(time);
    sprintf(packet_former, "TIME0");
    cJSON_AddItemToObject(packet, packet_former, json_value);
    json_value = cJSON_CreateString(message);
    sprintf(packet_former, "MESSAGE0");
    cJSON_AddItemToObject(packet, packet_former, json_value);
    packet_str = cJSON_Print(packet);
    
    return packet_str;
}

char* mx_add_message_by_id(char* packet) {
    printf("SEG FAULT - 1\n\n");
    int message_id = atoi(get_value_by_key(packet, "MESSAGEID"));
    char* time = get_value_by_key(packet, "TIME");
    char* message = get_value_by_key(packet, "MESSAGE");
    int chat_id = atoi(get_value_by_key(packet, "CHATID"));
    char* sender = get_value_by_key(packet, "SENDER");
    char* to = get_value_by_key(packet, "TO");
    printf("SEG FAULT - 2\n\n");


    if(message_id == 0)
    	mx_add_last_message(chat_id, message, time, sender);
    else
    	mx_add_message_with_id(message_id, chat_id, message);
    printf("SEG FAULT - 1\n\n");
    char* return_packet = mx_json_packet_former_from_list(message, time, sender, chat_id, to);
    printf("SEG FAULT - 2\n\n");
    return return_packet;
}
