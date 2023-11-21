#include "shell.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

/**
 * _puts - Prints a string to the standard output stream(like fprintf)
 * @str: The string to print
 *
 * Return: Void
 */
void _puts(char *str)
{
	size_t len;
	ssize_t num_written;

	len = len_str(str);
	num_written = write(STDOUT_FILENO, str, len);
	if (num_written == -1)
	{
		perror("write");
	}
}

void _putserr(char *error){

    size_t len;
    ssize_t num_written;

    len = len_str(error);
    num_written = write(STDERR_FILENO, error, len);
    if(num_written == -1){
        perror("write");
    }
}

int _putchar(char c){
    return (write(1, &c, 1));
}
