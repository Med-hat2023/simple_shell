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
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fileName = av[0];
	if (info->argumentCount)
	{
		info->argumentVector = strtow(info->argumentCount, " \t");
		if (!info->argumentVector)
		{

			info->argumentVector = malloc(sizeof(char *) * 2);
			if (info->argumentVector)
			{
				info->argumentVector[0] = _strdup(info->argumentCount);
				info->argumentVector[1] = NULL;
			}
		}
		for (i = 0; info->argumentVector && info->argumentVector[i]; i++)
			;
		info->argumentcount = i;

		replace_alias(info);
		replace_vars(info);
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
