#include "shell.h"

/**
 * displayCommandLog - with line numbers.
 *
 * @shellInfo: Structure containing potential arguments.
 *	Used to maintain a constant function prototype.
 * Return: Always returns 0.
 */
int displayCommandLog(info_t *shellInfo)
{
	print_list(shellInfo->commandList);
	return (0);
}

/**
 * dissolve_alias_connection- separates an alias from a
 * specified character sequence
 * @data_info: Information structure
 * @target_sequence: The character sequence representing the alias
 *
 * Return: (0) on success, (1) on error
 */
int dissolve_alias_connection(info_t *data_info, char *target_sequence)
{
	char *position, character;
	int result;

	position = FindCharacter(target_sequence, '=');
	if (!position)
	return (1);
	character = *position;
	*position = 0;
	result = delete_node_at_index(&(data_info->alternateName),
	get_node_index(data_info->alternateName, node_starts_with(data_info->
			alternateName, target_sequence, -1)));
	*position = character;
	return (result);
}


/**
 * associate_string_with_alias- maps a string to an alias
 * @data_info: Information structure
 * @target_sequence: The string representing the alias
 *
 * Return: 0 on success, 1 on error
 */
int associate_string_with_alias(info_t *data_info, char *target_sequence)
{
	char *position = FindCharacter(target_sequence, '=');

	if (position == NULL)
	{
	return (1);
	}
	else if
		(*++position == '\0')
	{
	return (dissolve_alias_connection(data_info, target_sequence));
	}
	else
	{
	dissolve_alias_connection(data_info, target_sequence);
	return (add_node_end(&(data_info->alternateName),
				target_sequence, 0) == NULL);
	}
}

/**
 * display_entry - prints an entry string
 * @displayed_entry: the entry node to be displayed
 *
 * Return:(0) on success, (1) on error
 */
int display_entry(list_t *displayed_entry)
{
	if (displayed_entry)
	{
	char *separator = FindCharacter(displayed_entry->string, '=');
	char *entry_value = displayed_entry->string;

	while (entry_value <= separator)
	{
	_putchar(*entry_value);
	entry_value++;
	}

	_putchar('\'');
	_puts(separator + 1);
	_puts("'\n");

	return (0);
	}
	return (1);
}


/**
 * execute_alias_operations - performs operations similar to
 * the alias built-in (man alias)
 * @arguments_info: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 *
 * Return: Always (0)
 */
int execute_alias_operations(info_t *arguments_info)
{
	int index = 0;
	char *position = NULL;
	list_t *current_entry = NULL;

	if (arguments_info->argumentcount == 1)
	{
	current_entry = arguments_info->alternateName;
	do {
	display_entry(current_entry);
	current_entry = current_entry->next;
	} while (current_entry);
	return (0);
	}

	index = 1;
	do {
	position = FindCharacter(arguments_info->argumentVector[index], '=');
	if (position)
	associate_string_with_alias(arguments_info, arguments_info->argumentVector[index]);
	else
	display_entry(node_starts_with(arguments_info->alternateName,
					arguments_info->argumentVector[index], '='));

	index++;
	} while (arguments_info->argumentVector[index]);

	return (0);
}

