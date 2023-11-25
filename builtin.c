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
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 *	Return: Always 0
 */
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 *	Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
