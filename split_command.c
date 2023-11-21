#include "shell.h"

/**
 * split_command - split command into characters  
 * @ptr_command: user input as string
 * Return: To a pointer
 */

char **split_command(char *ptr_command)
{
	size_t i = 0;
	int buffer_size = 0;
	char **_user_input = NULL;
	char *char_token = NULL;


	if (ptr_command == NULL)
		return NULL;

	for (i = 0; ptr_command[i]; i++)
	{
		if (ptr_command[i] == ' ')
			buffer_size++;
	}
	if ((buffer_size + 1) == len_str(ptr_command))
		return (NULL);

	_user_input = malloc(sizeof(char *) * (buffer_size + 2));

	if (_user_input == NULL)
		return (NULL);

	char_token = new_strtok(ptr_command, " \n\t\r");

	for (i = 0; char_token != NULL; i++)
	{
		_user_input[i] = char_token;
		char_token = new_strtok(NULL, " \n\t\r");
	}

	_user_input[i] = NULL;
	return (_user_input);
}

