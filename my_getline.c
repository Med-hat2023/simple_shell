#include "shell.h"
/**
 * my_getline - a function that do same thing og a pre defined getline
 * @lineptr: pointer to user input
 * @n: size of lineptr
 * return: -1 if fails or the bytes in line
*/
ssize_t my_getline(char **lineptr, size_t *n) {
    static char buffer[4096];
    static ssize_t buffer_index = 0;
    static ssize_t bytes_read = 0;
    size_t bytes_in_line = 0;
    int current_char;
    char *new_buffer;

    if (!lineptr || !n) {
        return -1;
    }

    if (*lineptr == NULL || *n == 0) {
        *n = 120; 
        *lineptr = (char *)malloc(*n);
        if (!*lineptr) {
            return -1;
        }
    }

    
    while (1) {
        if (buffer_index >= bytes_read) {
            bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
            buffer_index = 0;

            if (bytes_read <= 0) {
                break;
            }
        }

        while (buffer_index < bytes_read) {
            if (bytes_in_line + 1 >= *n) {
                *n *= 2;
                new_buffer = (char *)my_realloc(*lineptr, *n);
                if (!new_buffer) {
                    free(*lineptr);
                    return -1;
                }
                *lineptr = new_buffer;
            }

            current_char = buffer[buffer_index++];
            (*lineptr)[bytes_in_line++] = current_char;

            if (current_char == '\n') {
                break;
            }
        }

        if (current_char == '\n' || bytes_read == 0) {
            (*lineptr)[bytes_in_line] = '\0';
            break;
        }
    }

    if (bytes_in_line == 0) {
        free(*lineptr);
        *lineptr = NULL;
        return -1;
    }

    return bytes_in_line;
}
