#include "server.h"

static void deamon_failed_output(int cases) {
    if (cases == 1) {
        write(2, "error: deamon launch failed\n", 28);
        write(2, "forking error\n", 15);
        exit(EXIT_FAILURE);
    }
    if (cases == 2) {
        write(2, "error: deamon launch failed\n", 28);
        write(2, "writting log error\n", 19);
        exit(EXIT_FAILURE);
    }
}

static void deamon_successfull_output(pid_t pid) {
    write(1, "uchat_server started successfully\n", 34);
    write(1, "uchat_server pid: ", 18);
    mx_printint(pid);
    write(1, "\nto STOP uchat_server: kill <uchat_server pid>\n", 47);
    write(1, "if you lost uchat_server pid: ps -ax | grep uchat_server\n", 57);
}

void mx_deamon_start(void) {
    pid_t pid;

    //forking child process of server
    pid = fork();
    if (pid < 0) //if forking failed
        deamon_failed_output(1);
    if (pid > 0 ) //if forking successful, exit from parent process
        exit(EXIT_SUCCESS);
    else {
        deamon_successfull_output(getpid()); //useful output about deamon
        umask(0);   //make files available to read/write
        close(STDIN_FILENO);    //close input from terminal
        close(STDOUT_FILENO);   //close output to terminal
        close(STDERR_FILENO);   //close error stream
        setsid();   //make child process parent, detach from terminal
    }
}
