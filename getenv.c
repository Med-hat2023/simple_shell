#include "shell.h"

/**
 * sync_and_get_environment - Synchronizes and retrieves
 * the environment variables
 * @data: Structure containing potential arguments.
 * Used to maintain
 *	constant function prototype.
 * Return: Pointer to an array of strings representing
 * the environment variables.
 */
char **sync_and_get_environment(info_t *data)
{
	if (!data->environ || data->env_changed)
	{
	data->environ = list_to_strings(data->environmentVariables);
	data->env_changed = 0;
	}

	return (data->environ);
}

/**
 * remove_environment_variable - Removes an environment variable
 * @data: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 * @variable: The string representing the environment variable to remove.
 * Return: 1 if the variable is deleted, 0 otherwise.
 */
int remove_environment_variable(info_t *data, char *variable)
{
	list_t *current_node = data->environmentVariables;
	size_t index = 0;
	char *position;

	if (!current_node || !variable)
	return (0);

	do {
	position = starts_with(current_node->string, variable);
	if (position && *position == '=')
	{
	data->env_changed = delete_node_at_index(&
			(data->environmentVariables), index);
	index = 0;
	current_node = data->environmentVariables;
	continue;
	}
	current_node = current_node->next;
	index++;
	} while (current_node);

	return (data->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *	or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *	Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->environmentVariables;
	while (node)
	{
		p = starts_with(node->string, var);
		if (p && *p == '=')
		{
			free(node->string);
			node->string = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->environmentVariables), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
