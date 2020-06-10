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

#define CHILD 0

static GtkWidget *grid;

void error(char *msg, int status);
void back_to_menu(GtkWidget *back, int sockfd);
void main_menu(int sockfd);


