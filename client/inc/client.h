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
void do_login(GtkWidget *entryspawn, int sockfd);
void create_row(GtkWidget *labell, gpointer data);

static GtkWidget *login;
static GtkWidget *nickname;
static GtkWidget *Password;
static GtkWidget *SecondPassword;
static GtkWidget *Registration;
//static GtkWidget *newbutton;
static GtkWidget *fixed;
static GtkWidget *window;
static GtkWidget *grid;
static GtkWidget *labell;
static GtkWidget *labell2;
static GtkWidget *labell3;
static GtkWidget *scroll;
static GtkWidget *listbox;
static GtkWidget *row;
static GtkWidget *gridmenu;
static GtkWidget *labellmenu;
static GtkWidget *labellmenu2;
static GtkWidget *labellmenu3;
//static GtkWidget *iconn;
static GtkWidget *icon;
static GtkWidget *leftbox;
static GtkWidget *rightbox;
static GtkWidget *downbox;
static GtkWidget *leftmenu;
static GtkWidget *searchmenu;
static GtkWidget *newchatbutton;

static GtkWidget *newmessedgentry;

