#include "shell.h"

/**
 * exit_shell - exit the shell
 * @arg: the direction argument.
 * @lineptr: input string
 * @_exit: exit value
 * Return: None
 */
void exit_shell(char **arg, char *lineptr, int _exit)
{
    int status = 0;

    if (!arg[1])
    {
        free(arg);
        free(lineptr);
        exit(_exit);
    }

    status = stringToInt(arg[1]); /* convert string into integer */

    free(arg);
    free(lineptr);

    exit(status);
}
