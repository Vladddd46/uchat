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

typedef struct client_context_s {
	int sockfd;
} client_context_t;


void error(char *msg, int status);
void back_to_menu(GtkWidget *back, int sockfd);
void main_menu();
void do_login(GtkWidget *entryspawn, int sockfd);
void create_row(GtkWidget *labell, gpointer data);
void create_message(GtkWidget *newmessedgentry, gpointer data);
void end_message (GtkWidget *widget, GtkWidget *message);
char *get_text_of_textview(GtkWidget *text_view);
// Json lib. API
char *json_packet_former(int num, ...);
char *get_value_by_key(char *json_str, char *key);
void make_registration(GtkWidget *Registration, client_context_t *client_context);

// Logic
void do_registration(GtkWidget *Registration, client_context_t *client_context);

GtkWidget *entryspawn;
GtkWidget *login;
GtkWidget *nickname;
GtkWidget *Password;
GtkWidget *SecondPassword;
GtkWidget *Registration;
//static GtkWidget *newbutton;
GtkWidget *fixed;
GtkTextBuffer *textbuffer;
GtkWidget *window;
GtkWidget *grid;
GtkWidget *labell;
GtkWidget *labell2;
GtkWidget *labell3;
GtkWidget *scroll;
GtkWidget *listbox;
GtkWidget *listboxmess;
GtkWidget *row;
GtkWidget *gridmenu;
GtkWidget *labellmenu;
GtkWidget *labellmenu2;
GtkWidget *labellmenu3;
GtkWidget *icon;
GtkWidget *leftbox;
GtkWidget *rightbox;
GtkWidget *downbox;
GtkWidget *leftmenu;
GtkWidget *searchmenu;
GtkWidget *newchatbutton;

GtkWidget *newmessedgentry;
GtkWidget *scrollmess;
GtkWidget *fileMenu;
GtkWidget *ebox;
GtkWidget *edit;
GtkWidget *delet;
GtkWidget *editmessedgentry;
GtkWidget *editbox;
