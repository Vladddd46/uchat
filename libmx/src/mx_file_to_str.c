#include "libmx.h"

/*
 * Retrives data from file and puts it in returned str.
 */
char *mx_file_to_str(char *file) {
    char buff[1];
    int data_len;
    int fd = open(file, O_RDONLY);
    if (fd == -1)
        return NULL;
    data_len = 0;
    while (read(fd, buff, 1))
        data_len++;
    // Reset position of the file back to the beginning.
    lseek(fd, 0L, 0);
    // Allocate mem for data from file.
    char *str = mx_strnew(data_len);
    int index = 0;
    // Writing data to str.
    while(data_len){
        read(fd, buff, 1);
        str[index] = buff[0];
        index++;
        data_len--;
    }
    close(fd);
    return str;
}

