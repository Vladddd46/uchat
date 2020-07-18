#include "client.h"
 /// все вызовы функций гтк запихни в мейн поток(Денис для Дениса)
client_context_t *client_context;

static void destroy(GtkWidget *widget, gpointer data){
  gtk_main_quit();
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
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    main_menu();

    gtk_main(); 
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
    if (client_context == NULL)
        error("Client context malloc error", -1);
    client_context->sockfd = sockfd;
}

static void received_packet_analyzer(char *packet_type, char *packet) {
    printf("%s\n",packet );
    if (!strcmp(packet_type, "reg_s"))
        registration_system(client_context->sockfd, packet);
    else if (!strcmp(packet_type, "login_s"))
        login_system(client_context, packet);
    else if (!strcmp(packet_type, "find_user_s"))
        draw_list_box_system(packet);
    else if (!strcmp(packet_type, "add_new_user_s")){
       if(mx_strcmp(get_value_by_key(packet_type, "STATUS"), "false") == 1){
        printf("%s\n","1" );
            remake_chats(packet);
       }
        else{
            printf("%s\n","2" );
            close_window();
            printf("%s\n","3" );
        }
    }
    else if (!strcmp(packet_type, "msg_s"))
        create_row_system(client_context, packet);
     else if (!strcmp(packet_type, "add_msg_s"))
        create_row_system_new(client_context, packet);

}

/*
 * Thread, which receives packets from server.
 * When packet received, it is analyzed.
 * Depending on packet gui changes.
 */
static void *server_communication(void *param) {
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
        packet      = packet_receive(client_context->sockfd);
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
    int sockfd                     = mx_socket();
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





