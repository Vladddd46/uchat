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
	char *username;
	char *allusers;
	int indexrow;
	int counter;
} client_context_t;

struct struct_type {
	char *pack;
	int number;
	char *login;
	char *nickname;
	};

typedef struct s_s_glade {
 char *pack;
 int number;
 char *login;
 char *nickname;
}           t_s_glade;



client_context_t *client_context;
// какие то непонятные функции Дениса. PS. структурируй их пожалуйста.
void close_window();
gboolean button_release (GtkWidget *widget, GdkEventKey *event, gpointer data);
void download_messages(GtkWidget *widget, gpointer data);
gboolean my_keypress_function (GtkWidget *widget, GdkEventKey *event, gpointer data);
void create_row_system_new(client_context_t *client_context, char *packet);
int show_widget(GtkWidget *widget);
void remake_chats(char *pack);
void back_to_menu(GtkWidget *back, client_context_t *client_context);
void main_menu();
gboolean draw_message_menu(void *data);
gboolean create_message_system(void *data);
gboolean create_row(void * data);
gboolean create_message(void * data);
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
gboolean mini_button_release (GtkWidget *widget, GdkEventKey *event, gpointer data);
gboolean add_new_friend (GtkWidget *newchatbutton, gpointer data);
void draw_list_box_system(char *packet);
void dialog(GtkWidget *widget, gpointer data );
gboolean draw_list_box(void *data);
// gboolean mini_my_keypress_function (GtkWidget *widget, GdkEventKey *event, gpointer data);


// main
void argv_validator(int argc, char **argv);
int mx_socket();
struct sockaddr_in mx_client_address_describer(int port);

// Logic
void do_registration(GtkWidget *Registration, client_context_t *client_context);
void registration_system(int socket, char *packet);
void login_system(client_context_t *client_context, char *packet);
void create_row_system(client_context_t *client_context, char *packet);
//mini приставка для виджетов в окне добавления юзеров
GtkWidget *minibuttonfind;
GtkWidget *minieventbox;
GtkWidget *minibutton;
GtkWidget *minilabell2;
GtkWidget *minilabell;
GtkWidget *minirow;
GtkWidget *miniwindow;
GtkWidget *minibox;
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
GtkWidget *screp;
GtkWidget *buttonrefresh;
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

GtkWidget *editfixed;
GtkWidget *editwindow;

