#include "shell.h"

/**
 * main - main function
 * @ac: count of arguments
 * @av: arguments
 * @env: environment
 * Return: exit_status = 0.
 */
int main(int ac, char **av, char **env)
{
	(void)ac;
	run_shell(env, av);
	return 0;
}

