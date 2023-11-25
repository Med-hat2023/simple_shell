#include "shell.h"

/**
 * exitShell - Exit the shell with a specified exit status.
 *
 * @cmdInfo: Structure containing potential arguments.
 *	Used to maintain a constant function prototype.
 * Return: Exits with a given exit status (0)
 *	if cmdInfo->commandArguments[0] != "exit".
 */
int exitShell(info_t *cmdInfo)
{
	int exitCode;

	/* Check if there is an exit argument */
	if (cmdInfo->argv[1])
	{
	exitCode = _erratoi(cmdInfo->argv[1]);

	if (exitCode == -1)
	{
	cmdInfo->exitStatus = 2;
	print_error(cmdInfo, "Illegal number: ");
	_eputs(cmdInfo->argv[1]);
	_eputchar('\n');
	return (1);
	}

	cmdInfo->exitErrorNumber = exitCode;
	return (-2);
	}

	cmdInfo->exitErrorNumber = (-1);
	return (-2);
}

/**
 * changeCurrentDirectory - Change the current directory of the process.
 *
 * @shellInfo: Structure containing potential arguments.
 *	Used to maintain a constant function prototype.
 * Return: Always returns 0.
 */
int changeCurrentDirectory(info_t *shellInfo)
{
char *currentDir, *newDir, directoryBuffer[1024];
int chdirResult;

currentDir = getcwd(directoryBuffer, 1024);
	if (!currentDir)
	_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!shellInfo->argv[1])
	{
	newDir = _getenv(shellInfo, "HOME=");
	if (!newDir)
	chdirResult = /* TODO: what should this be? */
	chdir((newDir = _getenv(shellInfo, "PWD=")) ? newDir : "/");
	else
	chdirResult = chdir(newDir);
	}
	else if (_strcmp(shellInfo->argv[1], "-") == 0)
	{
	if (!_getenv(shellInfo, "OLDPWD="))
	{
	_puts(currentDir);
	_putchar('\n');
	return (1);
	}
	_puts(_getenv(shellInfo, "OLDPWD=")), _putchar('\n');
	chdirResult = /* TODO: what should this be? */
	chdir((newDir = _getenv(shellInfo, "OLDPWD=")) ? newDir : "/");
	}
	else
	{
	chdirResult = chdir(shellInfo->argv[1]);
	}
	if (chdirResult == -1)
	{
	print_error(shellInfo, "can't cd to ");
	_eputs(shellInfo->argv[1]), _eputchar('\n');
	}
	else
	{
	_setenv(shellInfo, "OLDPWD", _getenv(shellInfo, "PWD="));
	_setenv(shellInfo, "PWD", getcwd(directoryBuffer, 1024));
	}
	return (0);
}

/**
 * displayShellHelp - Display help information for the shell command.
 *
 * @commandInfo: Structure containing potential arguments.
 *	Used to maintain a constant function prototype.
 * Return: Always returns 0.
 */
int displayShellHelp(info_t *commandInfo)
{
	char **arguments = commandInfo->argv;

	_puts("Welcome to the Shell Help Center!\n");

	/* Additional help information can be added here */

	/* Displaying the arguments */

	while (*arguments)
	{
	_puts(*arguments);
	_puts(" ");
	arguments++;
	}

	_putchar('\n');

	return (0);
}

