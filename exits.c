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
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
