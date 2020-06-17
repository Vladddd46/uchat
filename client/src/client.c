#include "client.h"


static GtkWidget *login;
static GtkWidget *password;
static GtkWidget *SecondPassword;
static GtkWidget *Registration;
//static GtkWidget *newbutton;
static GtkWidget *fixed;
static GtkWidget *window;
static GtkWidget *grid;
//static GtkWidget *iconn;

//static int n = 98;
//static int sockfd = 0;

static void destroy(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}


void back_to_menu(GtkWidget *back, int sockfd){
    gtk_widget_destroy(grid);
    gtk_widget_destroy(back);
    main_menu(sockfd);
}

/*
 * Checks, whether format of login, user specified, is correct.
 * In case of incorrect login return 1.
 */
static int login_validator(char *user_login) {
    if (mx_is_in_str(user_login, ' '))
        return 1;
    return 0;
}

/*
 * Checks, whether format of password, user specified, is correct.
 * In case of incorrect password return 1.
 */
static int password_validator(char *user_password) {
    if (mx_is_in_str(user_password, ' '))
        return 1;
    return 0;
}

// Implements login functionality.
void do_login(GtkWidget *entryspawn, int sockfd) {
    // Getting input from input boxes.
    char *bufferLogin    = (char *)gtk_entry_get_text(GTK_ENTRY(login));
    char *bufferPassword = (char *)gtk_entry_get_text(GTK_ENTRY(password));
    
    // Validation of login and password format.
    if (login_validator(bufferLogin)) {
        write(2, "DEBUG: incorrect login fromat\n", 33);
        exit(1);                                       
    }
    else if (password_validator(bufferPassword)) {
        write(2, "DEBUG: incorrect password fromat\n", 35);
        exit(1);
    }

    // Froms and sends login packet to server and gets response.
    int status = login_system(sockfd, bufferLogin, bufferPassword);
    if (status      == LOGIN_SUCCESS) {
        printf("%s\n", "DEBUG: You are logged in\n");
        // TODO: запуск окна после логина
    }
    else if (status == LOGIN_FAIL) {
        printf("%s\n", "DEBUG: Wrong login or password\n");
        // TODO: ошибка: Неправильный логин/пароль
    }
    else if (status == LOGIN_PACKET_CREATION_ERROR) {
        printf("%s\n", "DEBUG: Packet was  not formed. Error occurred\n");
        // TODO: ошибка: Ошибка формирования пакета(в теории это возможно, на практике хз).
    }
}

void do_registration(GtkWidget *Registration, int sockfd){
    GtkWidget *back;

    gtk_widget_destroy(grid);

    grid = gtk_grid_new();
    gtk_widget_set_name(grid,"gride");
    gtk_fixed_put(GTK_FIXED (fixed), grid, 500,300);

    login = gtk_entry_new();
    gtk_entry_set_placeholder_text(login,"Login");
    gtk_grid_attach(GTK_GRID(grid), login, 0, 99, 2, 1);

    password = gtk_entry_new();
    gtk_entry_set_placeholder_text(password,"Password");
    gtk_grid_attach(GTK_GRID(grid), password, 0, 100, 2, 1);

    SecondPassword = gtk_entry_new();
    gtk_entry_set_placeholder_text(SecondPassword,"Confirm your password");
    gtk_grid_attach(GTK_GRID(grid), SecondPassword, 0, 101, 2, 1);

    Registration = gtk_button_new_with_label("Confirm registration");
    //g_signal_connect(Registration, "clicked", G_CALLBACK(do_registration), sockfd);
    gtk_grid_attach(GTK_GRID(grid), Registration, 0, 102, 2, 1);

    back = gtk_button_new_with_label("Back to Login");
    g_signal_connect(back, "clicked", G_CALLBACK(back_to_menu), sockfd);
    gtk_fixed_put(GTK_FIXED (fixed), back, 300,500);

    gtk_widget_show_all(window);
}

// Checks, wether user specified input correctly.
static void argv_validator(int argc, char **argv) {
    char *msg;

    if (argc != 3) {
        msg = "usage: ./client ip_address port\n";
        write(2, msg, (int)strlen(msg));
        exit(1);
    }

    int port = atoi(argv[2]);
    if (port == 0) {
        msg = "Invalid port number\n";
        write(2, msg, (int)strlen(msg));
        exit(1);
    }
}

void main_menu(int sockfd) {
    GtkWidget *quit, *entryspawn, *labell, *labell2;
    grid = gtk_grid_new();
    gtk_widget_set_name(grid,"gride");
    gtk_fixed_put(GTK_FIXED (fixed), grid, 300,200);
    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/yura.jpeg",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 100,100, GDK_INTERP_BILINEAR);
    GtkWidget *iconnn = gtk_image_new_from_pixbuf(iconn);
    // iconn = gtk_image_new_from_file("Unknown.jpeg");
     gtk_widget_set_name(iconnn,"image");
     gtk_grid_attach(GTK_GRID(grid), iconnn, 1, 98, 1, 1);

    login = gtk_entry_new();
    gtk_entry_set_placeholder_text(login,"Log In");
    gtk_widget_set_name(login,"login");
    gtk_grid_attach(GTK_GRID(grid), login, 1, 99, 1, 1);

    labell = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell, 1, 100, 1, 1);

    password = gtk_entry_new();
    gtk_entry_set_placeholder_text(password,"Password");
    gtk_widget_set_name(password,"Password");
    gtk_grid_attach(GTK_GRID(grid), password, 1, 101, 1, 1);
    
    labell2 = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell2, 1, 102, 1, 1);

    entryspawn = gtk_button_new_with_label("Login");
    g_signal_connect(entryspawn, "clicked", G_CALLBACK(do_login), sockfd);
    gtk_grid_attach(GTK_GRID(grid), entryspawn, 1, 103, 1, 1);

    Registration = gtk_button_new_with_label("Sign In");
    gtk_widget_set_name(Registration,"reg");
    g_signal_connect(Registration, "clicked", G_CALLBACK(do_registration), sockfd);
    gtk_grid_attach(GTK_GRID(grid), Registration, 1, 104, 1, 1);

    quit = gtk_button_new_with_label("X");
    gtk_grid_attach(GTK_GRID(grid), quit, 1, 105, 1, 1);
    g_signal_connect(quit, "clicked", G_CALLBACK(destroy), NULL);
    
    gtk_widget_set_size_request(GTK_WIDGET(window),1024,768);
    gtk_window_set_resizable(GTK_WIDGET(window), FALSE);
    gtk_widget_show_all(window);

}



void gui(int argc, char **argv, int sockfd){
    gtk_init(&argc, &argv);

    GtkCssProvider *provider = gtk_css_provider_new ();
    gtk_css_provider_load_from_path (provider,"./media/css/theme.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(provider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit), NULL);
    //gtk_widget_set_name(window,"window");

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    main_menu(sockfd);
    gtk_main();
}

static struct sockaddr_in client_address_describer(int port) {
    /* <del>
     * Создаем структуру, в которой описываем информацию клинта:
     * (bzero - заполняет все нулями)
     * 1. адресс сервера, к которому хотим подключиться.
     * 2. версия айпи-адресса AF_INET = IPv4
     * 3. порт сервера.
     */
    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Local Host
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);

    return client_addr;
}

static int Socket() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    error("Error while creating socket", sockfd);

    return sockfd;
}



int main(int argc, char **argv) {
    argv_validator(argc, argv);
    int port = atoi(argv[2]);

    // Creating IPv4 socket for TCP protocol.
    int sockfd = Socket();
    // Describing client address.
    struct sockaddr_in client_addr = client_address_describer(port);

    /* <del>
     * Конектимся к серверу.
     * 1 - дескриптор сокета. 2 - указатель на структуру с информацией о сервере/клиента. 3. размер структуры.
     */

    // Do the connection to server.
    int res = connect(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr));
    error("Error while connection", res);

    pthread_t thread;
    int err = pthread_create(&thread, NULL, listening_thread, &sockfd);
    gui(argc, argv, sockfd);
    write(sockfd, "hello server\n", 15);

}





