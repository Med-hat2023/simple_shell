#include "shell.h"

/**
 * my_cd - changes the current working directory of the shell
 * @args: array of arguments
 */
void my_cd(char **args)
{
    char *dir = args[1];
    int ret;

    /* If no argument is provided, change to HOME directory */
    if (dir == NULL)
    {
        char *home_dir = _getenv("HOME");
        if (home_dir == NULL)
        {
            _puts("cd: No HOME directory found\n");
            return;
        }
        dir = home_dir;
    }

    ret = chdir(dir);
    if (ret == -1)
    {
        perror("cd");
    }
}

