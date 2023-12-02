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
 * initialize_or_modify_environment_variable - Initializes a new or modifies
 * an existing environment variable
 * @data: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 * @variable: The string representing the environment variable.
 * @updated_value: The string representing the new value
 * of the environment variable.
 * Return: 0 on success, 1 on failure.
 */
int initialize_or_modify_environment_variable(info_t *data, char *variable,
		char *updated_value)
{
	char *buffer = NULL;
	list_t *current_node;
	char *position;

	if (!variable || !updated_value)
	return (1);

	do {
	buffer = malloc(_strlen(variable) + _strlen(updated_value) + 2);
	if (!buffer)
	return (1);

	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, updated_value);

	current_node = data->environmentVariables;
	while (current_node)
	{
	position = starts_with(current_node->string, variable);
	if (position && *position == '=')
	{
	free(current_node->string);
	current_node->string = buffer;
	data->env_changed = 1;
	return (0);
	}
	current_node = current_node->next;
	}

	add_node_end(&(data->environmentVariables), buffer, 0);
	free(buffer);
	data->env_changed = 1;
	return (0);
	} while (0);

	return (1);
}

