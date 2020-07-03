#include "server.h"

static int mx_callback(void* not_used, int argc, char** argv, char** az_con_name) {
	for(int i = 0; i < argc; i++) {
		printf("%s: %s\n", az_con_name[i], argv[i]);
	}
	return 0;
}

static chat_message_t* mx_fill_list(int chat_id, int from, int to) {
	chat_message_t* list = malloc(sizeof(chat_message_t));
	chat_message_t* head = list;
    sqlite3 *db;
    sqlite3_stmt *res;
    char sql[100];
    
    sqlite3_open("uchat.db", &db);
    sprintf(sql, "SELECT SENDER, TIME, MESSAGE FROM MESSAGES WHERE CHATID='%s';", mx_itoa(chat_id));
    sqlite3_prepare_v2(db, sql, -1, &res, 0);
    for(int i = 0; i < from; i++) {
    	sqlite3_step(res);
    }
    sqlite3_step(res);
    for(int i = from, j = 0; i < to && sqlite3_column_text(res, 0) != NULL; i++) {
        // printf("Value = %s -- %d\n", sqlite3_column_text(res, 2), i);
        list -> sender = mx_string_copy(sqlite3_column_text(res, 0));
        list -> time = mx_string_copy(sqlite3_column_text(res, 1));
        list -> message = mx_string_copy(sqlite3_column_text(res, 2));
        list -> next = (chat_message_t*)malloc(sizeof(chat_message_t));
        list = list -> next;
        list -> sender = NULL;
        list -> time = NULL;
        list -> message = NULL;
        list -> next = NULL;
        sqlite3_step(res);
        // printf("%s", sqlite3_column_text(res, 2));
    }
    // char* sql1 = "SELECT * FROM MESSAGES WHERE CHATID=1";
    // sqlite3_exec(db, sql1, mx_callback, NULL, NULL);
    // sqlite3_finalize(res);
    // for(int i = 0; i < 5; i++) {
    //     printf("Sender: %s   Time: %s\nMessage: %s\n\n", head -> sender, head -> time, head -> message);
    //     head = head -> next;
    // }
    return head;
}

static int mx_list_len(chat_message_t* chat) {
    int len = 0;
    chat_message_t* head = chat;

    while(chat -> message != NULL) {
        chat = chat -> next;
        len++;
    }
    head = chat;
    return len;
}

static char *mx_json_packet_former_from_list(chat_message_t* chat, int from) {
    int list_len = mx_list_len(chat);
    cJSON *packet = cJSON_CreateObject();
    char* packet_str = NULL;
    cJSON *json_value = cJSON_CreateString("msg_c");

    cJSON_AddItemToObject(packet, "TYPE", json_value);
    for(int i = 0; i < list_len; i++, from++) {
        json_value = cJSON_CreateString(mx_itoa(from));
        cJSON_AddItemToObject(packet, "ID", json_value);
        json_value = cJSON_CreateString(chat -> sender);
        cJSON_AddItemToObject(packet, "SENDER", json_value);
        json_value = cJSON_CreateString(chat -> time);
        cJSON_AddItemToObject(packet, "TIME", json_value);
        json_value = cJSON_CreateString(chat -> message);
        cJSON_AddItemToObject(packet, "MESSAGE", json_value);
        chat = chat -> next;
    }
    packet_str = cJSON_Print(packet);
    return packet_str;
}

char* mx_get_message(char* packet) {
    int chat_id = atoi(get_value_by_key(packet, "CHATID"));
    int from = atoi(get_value_by_key(packet, "FROM"));
    int to = atoi(get_value_by_key(packet, "TO"));

    chat_message_t* list = mx_fill_list(chat_id, from, to);
    char* return_packet = mx_json_packet_former_from_list(list, from);
    // while(list -> message != NULL) {
    // 	printf("Sender: %s   Time: %s\nMessage: %s\n\n", list -> sender, list -> time, list -> message);
    //     list = list -> next;
    // }
    printf("chat_id = %d\nfrom = %d\nto = %d\n", chat_id, from, to);
    printf("packet shmaket %s", return_packet);
    return return_packet;	
}
