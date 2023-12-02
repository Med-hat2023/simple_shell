#include "shell.h"

/**
 * initializeInfo - initializes info_t struct if not already initialized
 * @data: struct address
 */
void initializeInfo(info_t *data)
{
	if (data != NULL)
	{
	data->argumentCount = NULL;
	data->argumentVector = NULL;
	data->directory = NULL;
	data->argumentcount = 0;
	}
}

/**
 * configureInfo - initializes info_t struct and processes arguments
 * @data: struct address
 * @arguments: argument vector
 */
void configureInfo(info_t *data, char **arguments)
{
	int argument_count = 0;

	data->fileName = arguments[0];
	if (data->argumentCount)
	{
	data->argumentVector = strtow(data->argumentCount, " \t");
	if (!data->argumentVector)
	{
	data->argumentVector = malloc(sizeof(char *) * 2);
	if (data->argumentVector)
	{
	data->argumentVector[0] = _strdup(data->argumentCount);
	data->argumentVector[1] = NULL;
	}
	}
	while (data->argumentVector && data->argumentVector[argument_count])
	{
	argument_count++;
	}
	data->argumentcount = argument_count;

	replace_alias(data);
	replace_vars(data);
	}
}


/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
	ffree(info->argumentVector);
	info->argumentVector = NULL;
	info->directory = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->argumentCount);
		if (info->environmentVariables)
			free_list(&(info->environmentVariables));
		if (info->commandList)
			free_list(&(info->commandList));
		if (info->alternateName)
			free_list(&(info->alternateName));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(CLEAR_BUFFER);
	}
}
