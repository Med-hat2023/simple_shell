#include "shell.h"

/**
 * run_shell - main loop to run the shell
 * @env: environment
 * @av: arguments
 */
void run_shell(char **env, char **av)
{
	char *userInput = NULL;
	int exit_status = 0;

	while (1)
	{
		userInput = user_input();
		if (userInput)
		{
			exit_status = execute_shell(userInput, env, av);
			free(userInput);
		}
		else
		{
			/* Handling the non-interactive mode */
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			exit(exit_status);
		}
	}
}
