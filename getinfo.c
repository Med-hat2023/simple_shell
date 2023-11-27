#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argumentVector = NULL;
	info->path = NULL;
	info->argumentcount = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argumentVector = strtow(info->arg, " \t");
		if (!info->argumentVector)
		{

			info->argumentVector = malloc(sizeof(char *) * 2);
			if (info->argumentVector)
			{
				info->argumentVector[0] = _strdup(info->arg);
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
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
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
		_putchar(BUF_FLUSH);
	}
}
