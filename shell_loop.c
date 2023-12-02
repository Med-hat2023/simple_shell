#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
	initializeInfo(info);
		if (checkInteractiveMode(info))
			_puts("$ ");
		writeToStderr(CLEAR_BUFFER);
		r = get_input(info);
		if (r != -1)
		{
			configureInfo(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (checkInteractiveMode(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!checkInteractiveMode(info) && info->exitStatus)
		exit(info->exitStatus);
	if (builtin_ret == -2)
	{
		if (info->exitErrorNumber == -1)
			exit(info->exitStatus);
		exit(info->exitErrorNumber);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", exitShell},
		{"env", displayEnvironment},
		{"help", displayShellHelp},
		{"history", displayCommandLog},
		{"setenv", updateOrCreateEnvVariable},
		{"unsetenv", removeEnvironmentVariable},
		{"cd", changeCurrentDirectory},
		{"alias", execute_alias_operations},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argumentVector[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->directory = info->argumentVector[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->argumentCount[i]; i++)
		if (!isDelimiter(info->argumentCount[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, findEnvironmentValue(info, "PATH="), info->argumentVector[0]);
	if (path)
	{
		info->directory = path;
		fork_cmd(info);
	}
	else
	{
		if ((checkInteractiveMode(info) || findEnvironmentValue(info, "PATH=")
			|| info->argumentVector[0][0] == '/') && is_cmd(info, info->argumentVector[0]))
			fork_cmd(info);
		else if (*(info->argumentCount) != '\n')
		{
			info->exitStatus = 127;
			displayErrorInfo(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->directory, info->argumentVector, sync_and_get_environment(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->exitStatus));
		if (WIFEXITED(info->exitStatus))
		{
			info->exitStatus = WEXITSTATUS(info->exitStatus);
			if (info->exitStatus == 126)
				displayErrorInfo(info, "Permission denied\n");
		}
	}
}
