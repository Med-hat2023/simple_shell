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
	if (cmdInfo->argumentVector[1])
	{
	exitCode = convertStringToInt(cmdInfo->argumentVector[1]);

	if (exitCode == -1)
	{
	cmdInfo->exitStatus = 2;
	displayErrorInfo(cmdInfo, "Illegal number: ");
	printText(cmdInfo->argumentVector[1]);
	writeToStderr('\n');
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
	if (!shellInfo->argumentVector[1])
	{
	newDir = findEnvironmentValue(shellInfo, "HOME=");
	if (!newDir)
	chdirResult = /* TODO: what should this be? */
	chdir((newDir = findEnvironmentValue(shellInfo, "PWD=")) ? newDir : "/");
	else
	chdirResult = chdir(newDir);
	}
	else if (_strcmp(shellInfo->argumentVector[1], "-") == 0)
	{
	if (!findEnvironmentValue(shellInfo, "OLDPWD="))
	{
	_puts(currentDir);
	_putchar('\n');
	return (1);
	}
	_puts(findEnvironmentValue(shellInfo, "OLDPWD=")), _putchar('\n');
	chdirResult = /* TODO: what should this be? */
	chdir((newDir = findEnvironmentValue(shellInfo, "OLDPWD=")) ? newDir : "/");
	}
	else
	{
	chdirResult = chdir(shellInfo->argumentVector[1]);
	}
	if (chdirResult == -1)
	{
	displayErrorInfo(shellInfo, "can't cd to ");
	printText(shellInfo->argumentVector[1]), writeToStderr('\n');
	}
	else
	{
	_setenv(shellInfo, "OLDPWD", findEnvironmentValue(shellInfo, "PWD="));
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
	char **arguments = commandInfo->argumentVector;

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

