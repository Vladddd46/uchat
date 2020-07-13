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
#include "utils.h"

typedef struct client_context_s {
	int sockfd;
} client_context_t;

struct struct_type {
	char *pack;
	int number;
};

client_context_t *client_context;
// какие то непонятные функции Дениса. PS. структурируй их пожалуйста.
void back_to_menu(GtkWidget *back, client_context_t *client_context);
void main_menu();
void draw_message_menu(GtkWidget *entryspawn, client_context_t *client_context);
gboolean create_row(gpointer data, struct struct_type parm);
void create_message(GtkWidget *newmessedgentry, struct struct_type parm);
void end_message (GtkWidget *widget, GtkWidget *message);
char *get_text_of_textview(GtkWidget *text_view);
void make_registration(GtkWidget *Registration, client_context_t *client_context);
void do_login(GtkWidget *entryspawn, client_context_t *client_context);
void touch_room_signal(GtkWidget *listbox, void *socket);
void delete_message(GtkWidget *widget, GtkWidget *message);
void edit_message (GtkWidget *widget, GtkWidget *message);
void end_message (GtkWidget *widget, GtkWidget *message);
int show_popup(GtkWidget *widget, GdkEvent *event);
void add_new_user(GtkWidget *newchatbutton, gpointer data);


// main
void argv_validator(int argc, char **argv);
int  mx_socket();
struct sockaddr_in mx_client_address_describer(int port);
void mx_received_packet_analyzer(char *packet_type, char *packet, client_context_t *client_context);

// Logic
void do_registration(GtkWidget *Registration, client_context_t *client_context);
void registration_system(int socket, char *packet);
void login_system(client_context_t *client_context, char *packet);
void create_row_system(client_context_t *client_context, char *packet);
//mini приставка для виджетов в окне добавления юзеров

GtkWidget *miniwindow;
GtkWidget *minifixed;
GtkWidget *minilistbox;
GtkWidget *miniscroll;
GtkWidget *minientry;
GtkWidget *row;
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
GtkWidget *scrollnewmess;
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
GtkWidget *verticalbox;
GtkWidget *horizontalbox;
GtkWidget *newmessedgentry;
GtkWidget *scrollmess;
GtkWidget *fileMenu;
GtkWidget *ebox;
GtkWidget *edit;
GtkWidget *delet;
GtkWidget *editmessedgentry;
GtkWidget *editbox;
GtkWidget *messagebox;

