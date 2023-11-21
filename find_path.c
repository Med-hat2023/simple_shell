#include "shell.h"
/**
 * find_path - find the path.
 * @arg: command input of user (updated with the absolute path if found).
 * @env: environment.
 * Return: 0 if the absolute path is found, -1 otherwise.
 */
int find_path(char **arg, char **env)
{
	char *token = NULL, *path_rela = NULL, *path_absol = NULL;
	struct stat stat_lineptr;
	size_t value_path;
	size_t command;

	if (stat(*arg, &stat_lineptr) == 0)
		return (-1);

	path_rela = extract_path(env);
	if (!path_rela)
		return (-1);
    token = new_strtok(path_rela, ":");

	while (token)
	{
		value_path = len_str(token);
		command = len_str(*arg);

		path_absol = malloc(sizeof(char) * (value_path + command + 2));
		if (!path_absol)
		{
			free(path_rela);
			return (-1);
		}
		path_absol = _strcpy(path_absol, token);
		_strcat(path_absol, "/");
		_strcat(path_absol, *arg);

		if (stat(path_absol, &stat_lineptr) == 0)
		{
			*arg = path_absol;
			free(path_rela);
			return (0);
		}

		free(path_absol);
		token = new_strtok(NULL, ":");
	}
    free(path_rela);
	return (-1);
}

