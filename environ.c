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
	printText("Invalid number of arguments. Please provide the correct number.\n");
	return (1);
	}
	if (initialize_or_modify_environment_variable(information, information->argumentVector[1],
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
	printText("Insufficient arguments.\n");
	} while (0);

	return (1);
	} do
	{
	remove_environment_variable(information, information->argumentVector[index]);
	index++;
	} while (index <= information->argumentcount);

	return (0);
}

/**
 * initializeEnvironmentList - Create and initialize environment linked list
 * @inputInfo: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 * Return: Always 0
 */
int initializeEnvironmentList(info_t *inputInfo)
{
	list_t *envList = NULL;
	size_t index = 0;

	while (environ[index])
	{
	add_node_end(&envList, environ[index], 0);
	index++;
	}

	inputInfo->environmentVariables = envList;
	return (0);
}

