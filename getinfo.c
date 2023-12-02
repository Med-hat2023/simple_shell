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
 * releaseDataaResources - frees resources allocated for dataa_t struct
 * @dataa: struct address
 * @freeAll: true if freeing all fields
 */
void releaseDataaResources(info_t *dataa, int freeAll)

{
	ffree(dataa->argumentVector);
	dataa->argumentVector = NULL;
	dataa->directory = NULL;

	if (freeAll)
	{
	if (!dataa->cmd_buf)
	{
	free(dataa->argumentCount);
	}
	else
	{
	if (dataa->environmentVariables)
	free_list(&(dataa->environmentVariables));

	if (dataa->commandList)
	free_list(&(dataa->commandList));

	if (dataa->alternateName)
	free_list(&(dataa->alternateName));

	ffree(dataa->environ);
	dataa->environ = NULL;

	bfree((void **)dataa->cmd_buf);

	if (dataa->readfd > 2)
	close(dataa->readfd);

	_putchar(CLEAR_BUFFER);
	}
	}
}


