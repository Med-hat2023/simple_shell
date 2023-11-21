#include "shell.h"
/**
 * user_input - take the input from the user.
 * Return: return input user as string
 */

char *user_input(void)
{
	char *pointer = NULL;
	size_t buffer_size = 0;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "simple shell$ ", 13);

	if (getline(&pointer, &buffer_size, stdin) == -1)
	{
		free(pointer);
		return (NULL);
	}

	return (pointer);
}

