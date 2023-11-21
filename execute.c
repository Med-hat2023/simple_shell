#include "shell.h"

/**
 * execute - fork function
 * @arg: path value
 * @av: name of prog
 * @env: environment
 * @ptr: user command
 * @np: process id
 * @c: Checker
 * Return: 0 on success or an error code
 */
int execute(char **arg, char **av, char **env, char *ptr, int np, int c)
{
    /* In this function, we will create a child process from the parent one */
    pid_t child;
    int status;
    char *format = "%s: %d: %s: not found\n";

    child = fork(); /* Create a child process */

    if (child == 0)
    {
        if (execve(arg[0], arg, env) == -1)
        {
            fprintf(stderr, format, av[0], np, arg[0]);

            if (!c)
                free(arg[0]); /* Checker for new test */
            free(arg);
            free(ptr);
            exit(errno);
        }
    }
    else
    {
        wait(&status);

        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            return WEXITSTATUS(status);
    }
    return (0);
}

