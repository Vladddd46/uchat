#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <gtk/gtk.h>
#include "cJSON.h"
#include "libmx.h"

#define CHILD 0

#define LOGIN_SUCCESS 			     1
#define LOGIN_FAIL      		     2 
#define LOGIN_PACKET_CREATION_ERROR  3

static GtkWidget *grid;

void error(char *msg, int status);

// GUI
void back_to_menu(GtkWidget *back, int sockfd);
void main_menu(int sockfd);


void *listening_thread(void *arg);

