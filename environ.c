#include "shell.h"

/**
 * displayEnvironment - Display the current environment variables
 * @context: Pointer to a structure containing potential arguments.
 *	Used to maintain a consistent function prototype.
 * Return: Always returns 0.
 */
int displayEnvironment(info_t *context)
{
	if (context != NULL && context->environmentVariables != NULL)
	{
	print_list_str(context->environmentVariables);
	}
	return (0);
}

/**
 * findEnvironmentValue - Locates the value of an environment variable
 * @context: Structure containing relevant information. Used to maintain
 *	a consistent function prototype.
 * @varName: Name of the environment variable.
 *
 * Return: Returns the value of the environment variable, or NULL if not found.
 */
char *findEnvironmentValue(info_t *context, const char *varName)
{
	list_t *currentNode = context->environmentVariables;
	char *value = NULL;

	do {
	value = starts_with(currentNode->string, varName);
	if (value && *value)
	{
	return (value);
	}
	else
	{
	currentNode = currentNode->next;
	}
	} while (currentNode);

	return (NULL);
}
/***************************************/
/**
 * updateOrCreateEnvVariable - Update or Create Environment Variable
 *
 * This function is responsible for updating an existing environment variable
 * or creating a new one if it doesn't exist.
 *
 * @information: Structure containing potential arguments.
 * Return: (0) on success, (1) on failure.
 */
int updateOrCreateEnvVariable(info_t *information)
{
	int expectedArgCount = 4;	/* Change this to your desired number of arguments*/

	if (information->argc != expectedArgCount)
	{
	_eputs("Invalid number of arguments. Please provide the correct number.\n");
	return (1);
	}

	if (_setenv(information, information->argv[2], information->argv[3]) == 0)
	{
	return (0);	/* Success*/
	}
	else
	{
	_eputs("Failed to update or create environment variable\n");
	return (1);	/* Failure*/
	}
}
/****************************************************/
/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 *	Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->environmentVariables = node;
	return (0);
}
