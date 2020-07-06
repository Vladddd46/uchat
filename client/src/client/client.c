#include "client.h"

client_context_t *client_context;

bool  flag = FALSE;
static int messagenumber = 0;
static int n = 0;

char *get_text_of_textview(GtkWidget *text_view) {
    GtkTextIter start, end;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer((GtkTextView *)text_view);
    gchar *text;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    return text;
}

static void destroy(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}

int show_popup(GtkWidget *widget, GdkEvent *event) {
    const gint RIGHT_CLICK = 3;
    
    if (event->type == GDK_BUTTON_PRESS) {
        GdkEventButton *bevent = (GdkEventButton *) event;
        if (bevent->button == RIGHT_CLICK) {      
            gtk_menu_popup_at_pointer(GTK_MENU(widget), event);
            return TRUE;
        }
    }
    return FALSE;
}

void back_to_menu(GtkWidget *back, client_context_t *client_context){
    gtk_widget_destroy(grid);
    gtk_widget_destroy(back);
    main_menu(client_context->sockfd);
}

void delete_message(GtkWidget *widget, GtkWidget *message){
    if (flag == FALSE) {
        gtk_widget_destroy(message);
    }
}

void edit_message (GtkWidget *widget, GtkWidget *message){
    if (flag == FALSE) {
    char *editbuff = (char *)gtk_label_get_text(GTK_LABEL(message));
    gtk_widget_hide(newmessedgentry);
    editmessedgentry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(editmessedgentry),"Write a message...");
    gtk_widget_set_name(editmessedgentry,"newmessedgentry");
    gtk_box_pack_start(GTK_BOX(downbox),editmessedgentry, TRUE, TRUE, 0);
    gtk_entry_set_text(GTK_ENTRY(editmessedgentry),editbuff);
    gtk_widget_show(editmessedgentry);
    g_signal_connect(editmessedgentry, "activate", G_CALLBACK(end_message), message);
    
    editbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_widget_set_size_request(editbox,724,50);
    gtk_widget_set_name(editbox,"editbox");
    gtk_fixed_put(GTK_FIXED(fixed), editbox, 300,668);
    
    flag = TRUE;
    }
}

//отправка редактируемого сообщения
void end_message (GtkWidget *widget, GtkWidget *message){
    
    char *editbuff = (char *)gtk_entry_get_text(GTK_ENTRY(editmessedgentry));
    gtk_label_set_text(GTK_LABEL(message),editbuff);
    gtk_widget_destroy(editmessedgentry);
    gtk_widget_show(newmessedgentry);
    flag = FALSE;

}

void create_message(GtkWidget *newmessedgentry, gpointer data){
  GtkWidget *row;
    row = gtk_list_box_row_new();
    ebox = gtk_event_box_new();
    gtk_container_add(GTK_CONTAINER(row), ebox);
    gtk_widget_set_name(row,"message");
    gtk_list_box_row_set_selectable (GTK_LIST_BOX_ROW(row),FALSE);
    gtk_list_box_insert (GTK_LIST_BOX(listboxmess),row,n);
    messagenumber++;

    horizontalbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    //gtk_widget_set_name(gridmenu,"messagegrid");
    gtk_container_add(GTK_CONTAINER(ebox), horizontalbox);
    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/pokemon-2.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 32,32, GDK_INTERP_BILINEAR);
    icon = gtk_image_new_from_pixbuf(iconn);
    gtk_box_pack_start(GTK_BOX(horizontalbox),icon, FALSE, FALSE, 0);

    verticalbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_box_pack_start(GTK_BOX(horizontalbox),verticalbox, FALSE, FALSE, 0);

    labellmenu = gtk_label_new("Vlad");
    gtk_widget_set_name(labellmenu,"labellmenu");
    gtk_box_pack_start(GTK_BOX(verticalbox),labellmenu, FALSE, FALSE, 0);

    char *messageBuff = get_text_of_textview(newmessedgentry);
    labellmenu2 = gtk_label_new(messageBuff);
    gtk_widget_set_name(labellmenu2,"labellmenu2");
    gtk_box_pack_start(GTK_BOX(verticalbox),labellmenu2, FALSE, FALSE, 0);

    labellmenu3 = gtk_label_new("Yesterday");
    //gtk_grid_attach(GTK_GRID(gridmenu), labellmenu3, 2, 1, 1, 1);
    gtk_box_pack_start(GTK_BOX(horizontalbox),labellmenu3, FALSE, FALSE, 0);



 //menu with edit and delete button
    fileMenu = gtk_menu_new();
    g_signal_connect_swapped(G_OBJECT(ebox), "button-press-event", G_CALLBACK(show_popup), fileMenu);

    edit = gtk_menu_item_new_with_label("Edit");
    gtk_widget_show(edit);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), edit);
    g_signal_connect (edit, "activate", G_CALLBACK (edit_message), labellmenu2);

    delet = gtk_menu_item_new_with_label("Delete");
    gtk_widget_show (delet);
    gtk_menu_shell_append (GTK_MENU_SHELL (fileMenu), delet);
    g_signal_connect (delet, "activate", G_CALLBACK (delete_message), row);
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(newmessedgentry),textbuffer);

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

void make_registration(GtkWidget *Registration, client_context_t *client_context){
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
    gtk_entry_set_visibility(GTK_ENTRY(Password),FALSE);

    SecondPassword = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(SecondPassword),"Confirm your password");
    gtk_grid_attach(GTK_GRID(grid), SecondPassword, 1, 103, 1, 1);
    gtk_entry_set_visibility(GTK_ENTRY(SecondPassword),FALSE);

    labell2 = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell2, 1, 104, 1, 1);


    Registration = gtk_button_new_with_label("Sign Up");
    gtk_widget_set_name(Registration,"reg");
    g_signal_connect(Registration, "clicked", G_CALLBACK(do_registration), client_context);
    gtk_grid_attach(GTK_GRID(grid), Registration, 1, 105, 1, 1);

    labell3 = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell3, 1, 106, 1, 1);

    back = gtk_button_new_with_label("Back to Login");
    gtk_widget_set_name(back,"log");
    g_signal_connect(back, "clicked", G_CALLBACK(back_to_menu), client_context);
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

// Main window init.
void gui(int argc, char **argv, client_context_t *client_context) {
    gtk_init(&argc, &argv);

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path (provider,"./media/css/theme.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(provider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    //window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    main_menu();

    gtk_main();
}

static int Socket() {
    // Create socket TCP and IPv4
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    error("Error while creating socket", sockfd);

    return sockfd;
}

static struct sockaddr_in client_address_describer(int port) {
    /*
     * Create structure, where client address is described.
     * 1. server`s address
     * 2. ip version AF_INET = IPv4
     * 3. server`s port.
     */
    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Local Host
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);

    return client_addr;
}

void client_context_init(int sockfd) {
    client_context = (client_context_t *)malloc(sizeof(client_context_t));
    if (client_context == NULL) {
        char *msg = "Client context malloc error\n";
        write(2, msg, (int)strlen(msg));
        exit(1);
    }

    client_context->sockfd = sockfd;
}

// Read first 8 bytes from packet. (They represent the length of the packet.)
static int packet_length_determine(void) {
    char buf[8];
    bzero(buf, 8);
    recv(client_context->sockfd, buf, 8, 0);
    int packet_len = atoi(buf);

    return packet_len;
}

// Receiving packet from the socket.
static char *packet_receive(void) {
    int  packet_len = packet_length_determine();
    char *packet = mx_strnew(packet_len);
    int  index = 0;

    while(index < packet_len) {
        recv(client_context->sockfd, &packet[index], 1, 0);
        index++;
    }
    return packet;
}

static void received_packet_analyzer(char *packet_type, char *packet) {
    if (!strcmp(packet_type, "reg_s"))
        registration_system(client_context->sockfd, packet);
    else if (!strcmp(packet_type, "login_s"))
        login_system(client_context, packet);
    else if (!strcmp(packet_type, "find_user_s"))
        printf("%s\n", "find_user packet receive");
    else if (!strcmp(packet_type, "msg_s"))
        printf("%s\n", "msg packet received");
}

/*
 * Thread, which receives packets from server.
 * When packet received, it is analyzed.
 * Depending on packet gui changes.
 */
void *server_communication(void *param) {
    fd_set read_descriptors;
    struct timeval tv = wait_time(1, 0);
    int status;
    char *packet;
    char *packet_type;

    while(1) {
        FD_ZERO(&read_descriptors);
        FD_SET(client_context->sockfd, &read_descriptors);
        status = select(FD_SETSIZE, &read_descriptors, NULL, NULL, &tv);
        if (status <= 0) continue;
        // Receive packet from the server.
        packet      = packet_receive();
        if (packet == NULL)
            exit(1);
        packet_type = get_value_by_key(packet, "TYPE");
        received_packet_analyzer(packet_type, packet);
        free(packet_type);
        free(packet);
    }
    return NULL;
}

int main(int argc, char **argv) {
    argv_validator(argc, argv);
    int port                       = atoi(argv[2]);
    int sockfd                     = Socket();
    struct sockaddr_in client_addr = client_address_describer(port);

    // Do the connect to the server.
    int res = connect(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr));
    error("Error while connection", res);

    client_context_init(sockfd);
    pthread_t client_thread;
    int err = pthread_create(&client_thread, NULL, server_communication, NULL);
    error("Error while creating new thread.", err);

    // Gui initialization
    gui(argc, argv, client_context);
    free(client_context);
    return 0;
}





