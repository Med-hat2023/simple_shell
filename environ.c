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
/****************************************************/


/**
 * updateOrCreateEnvVariable - Initialize a new environment variable,
 *	or modify an existing one
 * @information: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 * Return: Always 0
 */
int updateOrCreateEnvVariable(info_t *information)
{
	if (information->argumentcount != 3)
	{
	_eputs("Invalid number of arguments. Please provide the correct number.\n");
	return (1);
	}
	if (_setenv(information, information->argumentVector[1],
				information->argumentVector[2]))
	return (0);
	return (1);
}


/**
 * removeEnvironmentVariable - Remove specified environment variables
 * @information: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 * Return: Always 0
 */
int removeEnvironmentVariable(info_t *information)
{
	int index = 1;

	if (information->argumentcount == 1)
	{ do
	{
	_eputs("Insufficient arguments.\n");
	} while (0);

	return (1);
	} do
	{
	_unsetenv(information, information->argumentVector[index]);
	index++;
	} while (index <= information->argumentcount);

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
