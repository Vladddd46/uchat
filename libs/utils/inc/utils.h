#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <netinet/in.h>
#include <sqlite3.h>
#include <pthread.h>
#include <stdbool.h>
#include "libmx.h"
#include "cJSON.h"
#include "crypt.h"

char *json_packet_former(int num, ...);
char *get_value_by_key(char *json_str, char *key);

void error(char *msg, int status);

// Packet formation functions.
char *packet_len_prefix_adder(char *packet);
char *packet_receive(int socket);
void mx_send(int socket, char *packet);

// Sets time select must wait.
struct timeval wait_time(int sec, int msec);
