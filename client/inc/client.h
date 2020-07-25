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
#include "libmx.h"
#include "utils.h"
#include "cJSON.h"

typedef struct client_context_s {
	int sockfd;
	char *username;
	char *allusers;
	int indexrow;
	int counter;
	char **mas;
	bool flag;
	bool Ukraine;
	bool edit;
	bool find;
	bool sticker;
	int guinumber;
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
void mx_sticker_menu(GtkWidget* widget, gpointer data);
void mx_stickerbool (GtkWidget* widget,gpointer data);
void mx_sticker_send_system(GtkWidget* widget, gpointer data);
void mx_findbool (GtkWidget* widget,gpointer data);
void mx_editbool (GtkWidget* widget,gpointer data);
void mx_close_window(GtkWidget *widget);
gboolean button_release (GtkWidget *widget, GdkEventKey *event, gpointer data);
void mx_download_messages(GtkWidget *widget, gpointer data);
gboolean my_keypress_function (GtkWidget *widget, GdkEventKey *event, gpointer data);
void mx_create_row_system_new(client_context_t *client_context, char *packet);
int show_widget(GtkWidget *widget);
void mx_remake_chats(char *pack);
void mx_back_to_menu(GtkWidget *back, client_context_t *client_context);
void mx_main_menu();
gboolean mx_draw_message_menu(void *data);
gboolean mx_create_message_system(void *data);
gboolean mx_create_row(void * data);
gboolean mx_create_message(void * data);
char *mx_get_text_of_textview(GtkWidget *text_view);
void mx_make_registration(GtkWidget *Registration, client_context_t *client_context);
void mx_do_login(GtkWidget *entryspawn, client_context_t *client_context);
void mx_touch_room_signal(GtkWidget *listbox, void *socket);
void mx_add_new_user(GtkWidget *newchatbutton, gpointer data);
gboolean mx_mini_button_release (GtkWidget *widget, GdkEventKey *event, gpointer data);
void mx_change_password_system(GtkWidget* widget, gpointer data);
void mx_editbool (GtkWidget* widget,gpointer data);
void mx_findbool (GtkWidget* widget,gpointer data);
void mx_draw_edit_profile(GtkWidget *widget, gpointer data);
void mx_stickerbool (GtkWidget* widget,gpointer data);
gboolean mx_add_new_friend (GtkWidget *widget, gpointer data);
gboolean mx_draw_list_box_system(void *data);
void mx_logout_system(GtkWidget *widget, gpointer data);
gboolean mx_draw_list_box(void *data);
void mx_switchlanguage_system(GtkSwitch *widget,
               gboolean   state,
               gpointer   user_data);
// gboolean mini_my_keypress_function (GtkWidget *widget, GdkEventKey *event, gpointer data);


// main
void argv_validator(int argc, char **argv);
int mx_socket();
// struct sockaddr_in mx_client_address_describer(int port,  char *address);

// Logic
void mx_do_registration(GtkWidget *Registration, client_context_t *client_context);
gboolean mx_registration_system(void *data);
void mx_login_system(client_context_t *client_context, char *packet);
gboolean mx_create_row_system(void *data);

// additional
void mx_null_error(char *msg);
char *mx_get_time();


//mini приставка для виджетов в окне добавления юзеров
GtkWidget *scrollm;
GtkWidget *back;
GtkWidget *stickermessage;
GtkWidget *stickerebox;
GtkWidget *stickerimage;
GtkWidget *stickerfixed;
GtkWidget *stickerwindow;
GtkWidget *sticker;
GtkWidget *changepassword;
GtkWidget *logout;
GtkWidget *editgrid;
GtkWidget *themelabel;
GtkWidget *languagelabel;
GtkWidget *switchtheme;
GtkWidget *switchlanguage;
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

