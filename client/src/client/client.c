#include "client.h"



static int messagenumber = 0;
static int n = 0;

static void destroy(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}


void back_to_menu(GtkWidget *back, int sockfd){
gtk_widget_destroy(grid);
gtk_widget_destroy(back);
main_menu(sockfd);
}

void do_login(GtkWidget *entryspawn, int sockfd){
    char *buffer = (char *)gtk_entry_get_text(GTK_ENTRY(login));
    char *bufferPassword = (char *)gtk_entry_get_text(GTK_ENTRY(Password));
    send(sockfd,buffer,sizeof(buffer),0);
    send(sockfd,bufferPassword,sizeof(bufferPassword),0);

    
        //another function

    gtk_widget_destroy(grid);
    scroll = gtk_scrolled_window_new(0,0);
    gtk_fixed_put(GTK_FIXED (fixed), scroll, 0,50);

    leftbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_widget_set_size_request(leftbox,300,50);
    gtk_widget_set_name(leftbox,"leftbox");
    gtk_fixed_put(GTK_FIXED (fixed), leftbox, 0,0);

    leftmenu = gtk_button_new();
    gtk_box_pack_start(GTK_BOX(leftbox), leftmenu, TRUE, TRUE, 0);
    gtk_widget_set_name(leftmenu,"leftmenu");
    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/menu_icon.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(iconn);
    gtk_button_set_image (GTK_BUTTON (leftmenu), icon);

    searchmenu = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(searchmenu),"Search");
    gtk_widget_set_name(searchmenu,"searchmenu");
    gtk_box_pack_start(GTK_BOX(leftbox),searchmenu, TRUE, TRUE, 10);
    

    newchatbutton = gtk_button_new();
    gtk_box_pack_end(GTK_BOX(leftbox), newchatbutton, TRUE, TRUE, 0);
    g_signal_connect(newchatbutton, "clicked", G_CALLBACK(create_row), NULL);
    iconn = gdk_pixbuf_new_from_file("./media/img/plus_icon.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(iconn);
    gtk_button_set_image (GTK_BUTTON (newchatbutton), icon);

    rightbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_widget_set_size_request(rightbox,724,50);
    gtk_widget_set_name(rightbox,"rightbox");
    gtk_fixed_put(GTK_FIXED (fixed), rightbox, 300,0);

    listbox = gtk_list_box_new();
    gtk_widget_set_name(listbox,"listboxleft");
    gtk_widget_set_size_request(scroll,300,718);
    gtk_container_add(GTK_CONTAINER(scroll), listbox);

    downbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_widget_set_size_request(downbox,724,50);
    gtk_widget_set_name(downbox,"downbox");
    gtk_fixed_put(GTK_FIXED (fixed), downbox, 300,718);

    newmessedgentry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(newmessedgentry),"Write a message...");
    gtk_widget_set_name(newmessedgentry,"newmessedgentry");
    gtk_box_pack_start(GTK_BOX(downbox),newmessedgentry, TRUE, TRUE, 0);
    g_signal_connect(newmessedgentry, "activate", G_CALLBACK(create_message), NULL);

    scrollmess = gtk_scrolled_window_new(0,0);
    gtk_fixed_put(GTK_FIXED (fixed), scrollmess, 300,50);
    gtk_widget_set_name(scrollmess,"scrollmess");
    gtk_widget_set_size_request(GTK_WIDGET(scrollmess),724,668);

    listboxmess = gtk_list_box_new();
    gtk_widget_set_name(listboxmess,"listboxmess");
    gtk_container_add(GTK_CONTAINER(scrollmess), listboxmess);

     gtk_widget_show_all(window);
}


void create_message(GtkWidget *newmessedgentry, gpointer data){
    GtkWidget *row;
    row = gtk_list_box_row_new();
    gtk_widget_set_name(row,"message");
    gtk_list_box_row_set_selectable (GTK_LIST_BOX_ROW(row),FALSE);
    gtk_list_box_insert (GTK_LIST_BOX(listboxmess),row,n);
    messagenumber++;

    gridmenu = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(row), gridmenu);
    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/pokemon-2.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(iconn);
    gtk_grid_attach(GTK_GRID(gridmenu), icon, 0, 0, 1, 2);

    labellmenu = gtk_label_new("Vlad");
    gtk_widget_set_name(labellmenu,"labellmenu");
    gtk_grid_attach(GTK_GRID(gridmenu), labellmenu, 1, 0, 1, 1);

    labellmenu2 = gtk_label_new("Kill me please \nHello");
    gtk_widget_set_name(labellmenu2,"labellmenu2");
    gtk_grid_attach(GTK_GRID(gridmenu), labellmenu2, 1, 1, 1, 1);

    labellmenu3 = gtk_label_new("Yesterday");
    gtk_grid_attach(GTK_GRID(gridmenu), labellmenu3, 2, 0, 1, 1);
    gtk_widget_set_name(labellmenu3,"labellmenu3");

    fileMenu = gtk_menu_new();
    gtk_menu_popup_at_pointer (GTK_MENU (fileMenu),trigger_event);
    Password = gtk_button_new_with_label("fdfdf");
    gtk_container_add(fileMenu,Password);

    gtk_widget_show_all(window);
}


void create_row(GtkWidget *labell, gpointer data){
    GtkWidget *row;
    row = gtk_list_box_row_new();
    gtk_widget_set_name(row,"chatrow");
    gtk_list_box_row_set_selectable (GTK_LIST_BOX_ROW(row),FALSE);
    gtk_list_box_insert (GTK_LIST_BOX(listbox),row,n);
    n++;

    gridmenu = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(row), gridmenu);
    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/pokemon-2.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(iconn);
    gtk_grid_attach(GTK_GRID(gridmenu), icon, 0, 0, 1, 2);

    labellmenu = gtk_label_new("Vlad");
    gtk_widget_set_name(labellmenu,"labellmenu");
    gtk_grid_attach(GTK_GRID(gridmenu), labellmenu, 1, 0, 1, 1);

    labellmenu2 = gtk_label_new("Kill me please");
    gtk_widget_set_name(labellmenu2,"labellmenu2");
    gtk_grid_attach(GTK_GRID(gridmenu), labellmenu2, 1, 1, 1, 1);

    labellmenu3 = gtk_label_new("Yesterday");
    gtk_grid_attach(GTK_GRID(gridmenu), labellmenu3, 2, 0, 1, 1);
    gtk_widget_set_name(labellmenu3,"labellmenu3");

    gtk_widget_show_all(window);
}


void make_registration(GtkWidget *Registration, int sockfd){
    GtkWidget *back;

    gtk_widget_destroy(grid);

    grid = gtk_grid_new();
    gtk_widget_set_name(grid,"gride");
    gtk_fixed_put(GTK_FIXED (fixed), grid, 350,175);

    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/pokeball.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 128,128, GDK_INTERP_BILINEAR);
    GtkWidget *iconnn = gtk_image_new_from_pixbuf(iconn);
     gtk_widget_set_name(iconnn,"image");
     gtk_grid_attach(GTK_GRID(grid), iconnn, 1, 98, 1, 1);

    login = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(login),"Login");
    gtk_grid_attach(GTK_GRID(grid), login, 1, 99, 1, 1);

    nickname = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(nickname),"Username");
    gtk_grid_attach(GTK_GRID(grid), nickname, 1, 100, 1, 1);

    labell = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell, 1, 101, 1, 1);

    Password = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Password),"Password");
    gtk_grid_attach(GTK_GRID(grid), Password, 1, 102, 1, 1);

    SecondPassword = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(SecondPassword),"Confirm your password");
    gtk_grid_attach(GTK_GRID(grid), SecondPassword, 1, 103, 1, 1);

    labell2 = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell2, 1, 104, 1, 1);


    Registration = gtk_button_new_with_label("Sign Up");
    gtk_widget_set_name(Registration,"reg");
    g_signal_connect(Registration, "clicked", G_CALLBACK(do_registration), NULL);
    gtk_grid_attach(GTK_GRID(grid), Registration, 1, 105, 1, 1);

    labell3 = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell3, 1, 106, 1, 1);

    back = gtk_button_new_with_label("Back to Login");
    gtk_widget_set_name(back,"log");
    g_signal_connect(back, "clicked", G_CALLBACK(back_to_menu), sockfd);
    gtk_grid_attach(GTK_GRID(grid), back, 1, 107, 1, 1);
    //gtk_fixed_put(GTK_FIXED (fixed), back, 550,540);

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
    GtkWidget *entryspawn;
    //GtkWidget *scroll;
    //GtkWidget *view;
    grid = gtk_grid_new();
    gtk_widget_set_name(grid,"gride");
    gtk_fixed_put(GTK_FIXED (fixed), grid, 350,175);

    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/pokeball.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 128,128, GDK_INTERP_BILINEAR);
    GtkWidget *iconnn = gtk_image_new_from_pixbuf(iconn);
    // iconn = gtk_image_new_from_file("Unknown.jpeg");
     gtk_widget_set_name(iconnn,"image");
     gtk_grid_attach(GTK_GRID(grid), iconnn, 1, 98, 1, 1);

    login = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(login),"Log In");
    gtk_widget_set_name(login,"login");
    gtk_grid_attach(GTK_GRID(grid), login, 1, 99, 1, 1);

    labell = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell, 1, 100, 1, 1);

    Password = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Password),"Password");
    gtk_widget_set_name(Password,"Password");
    gtk_grid_attach(GTK_GRID(grid), Password, 1, 101, 1, 1);
    
    labell2 = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell2, 1, 102, 1, 1);

    entryspawn = gtk_button_new_with_label("Login");
    gtk_widget_set_name(entryspawn,"log");
    g_signal_connect(entryspawn, "clicked", G_CALLBACK(do_login), sockfd);
    gtk_grid_attach(GTK_GRID(grid), entryspawn, 1, 103, 1, 1);

     labell3 = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell3, 1, 104, 1, 1);

    Registration = gtk_button_new_with_label("Sign In");
    gtk_widget_set_name(Registration,"reg");
    g_signal_connect(Registration, "clicked", G_CALLBACK(make_registration), sockfd);
    gtk_grid_attach(GTK_GRID(grid), Registration, 1, 105, 1, 1);

    gtk_widget_set_size_request(GTK_WIDGET(window),1024,768);
    //gtk_window_set_resizable(GTK_WIDGET(window), FALSE);
    gtk_widget_show_all(window);

}

// Main window init.
void gui(int argc, char **argv, int sockfd){
    gtk_init(&argc, &argv);

    GtkCssProvider *provider = gtk_css_provider_new();
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

    // char buf[1000];
    // while(recv(sockfd, buf, sizeof(buf), 0)) {
    //     printf(">>%s\n", buf);
    // }

    gtk_main();
}

int main(int argc, char **argv) {
    argv_validator(argc, argv);
    int port = atoi(argv[2]);

    /* <del>
     * Создаем сокет типа IPv4 для протокола TCP.
     */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    error("Error while creating socket", sockfd);

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

    /* <del>
     * Конектимся к серверу.
     * 1 - дескриптор сокета. 2 - указатель на структуру с информацией о сервере/клиента. 3. размер структуры.
     */

    int res = connect(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr));
    error("Error while connection", res);
    gui(argc,argv,sockfd);
    write(sockfd, "hello server\n", 15);

}





