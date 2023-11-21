#include "shell.h"

/**
 * extract_path - Extracts the value of the PATH variable from the environment.
 * @env: The environment array.
 * Return: A dynamically allocated string containing the value of PATH, or NULL on failure.
 */
char *extract_path(char **env)
{
    size_t i = 0, len = 0;
    char *path = NULL;
    size_t j;

    for (i = 0; env[i] != NULL; i++)
    {
        if (_strncmp(env[i], "PATH=", 5) == 0)
            break;
    }

    if (env[i] == NULL)
        return NULL;

    len = len_str(env[i]) - 5;

    path = malloc(sizeof(char) * (len + 1));
    if (path == NULL)
        return NULL;

    for (j = 0; j < len; j++)
    {
        path[j] = env[i][j + 5];
    }

    path[len] = '\0';

    return path;
}

