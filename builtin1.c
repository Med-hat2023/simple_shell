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

	position = _strchr(target_sequence, '=');
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
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (dissolve_alias_connection(info, str));

	dissolve_alias_connection(info, str);
	return (add_node_end(&(info->alternateName), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *	constant function prototype.
 *	Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alternateName;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alternateName, info->argv[i], '='));
	}

	return (0);
}
