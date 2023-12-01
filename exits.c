#include "shell.h"

/**
 * CustomStringCopy - Copies a portion of a source string to
 * an output string
 * @output: Pointer to the output string
 * @source: Pointer to the source string
 * @limit: Maximum number of characters to copy
 *
 * Description:
 *	This function copies up to 'limit' characters from
 *	the 'source' string to the
 *	'output' string. If the length of 'source'
 *	is less than 'limit', the
 *	remaining characters in 'output' are filled with null characters.
 *
 * Return:Pointer to the beginning of the output string.
 */

char *CustomStringCopy(char *output, char *source, int limit)
{
	int indexSource, indexFill;
	char *result = output;

	for (indexSource = 0; source[indexSource] != '\0' && indexSource <
						limit - 1; indexSource++)
	{
	output[indexSource] = source[indexSource];
	}

	for (indexFill = indexSource; indexFill < limit; indexFill++)
	{
	output[indexFill] = '\0';
	}

	return (result);
}

/**
 * ConcatenateLimited - Concatenates two strings with
 * a maximum limit
 * @destination: The first string to be concatenated
 * @source: The second string to be concatenated
 * @limit: The maximum number of characters to concatenate
 * from the source
 *
 * Description:
 *	This function concatenates the 'source'
 *	string to the 'destination' string,
 *	limiting the concatenation to 'limit' characters
 *	from the 'source' string.
 *	The resulting concatenated string is null-terminated.
 *
 * Return:Pointer to the beginning of the concatenated string.
 */
char *ConcatenateLimited(char *destination, char *source, int limit)
{
	int indexDest = 0, indexSrc = 0;
	char *result = destination;

	/* Find the end of the destination string*/
	do {
	if (destination[indexDest] == '\0')
	break;

	indexDest++;
	} while (1);

	/* Concatenate characters from the source to the destination*/
	do {
	if (source[indexSrc] == '\0' || indexSrc >= limit)
	break;

	destination[indexDest] = source[indexSrc];
	indexDest++;
	indexSrc++;
	} while (1);

	/* Null-terminate the resulting string*/
	if (indexSrc < limit)
	{
	destination[indexDest] = '\0';
	}

	return (result);
}

/**
 * FindCharacter - Finds a character in a string
 * @string: The string to be searched
 * @character: The character to look for
 *
 * Description:
 *	This function searches for the first occurrence
 *	of 'character' in the
 *	string 'str'. If found, it returns a pointer
 *	to the memory location of
 *	the character; otherwise, it returns NULL.
 *
 * Return:Pointer to the memory area in the string
 * where the character is found,
 *	or NULL if the character is not present.
 */
char *FindCharacter(char *string, char character)
{
	while (*string != '\0')
	{
	if (*string == character)
	return (string);
	string++;
	}

	return (NULL);
}

