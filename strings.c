#include "shell.h"

/**
 *_strcat - s1 string to another string.
 *@dest: char
 *@src: char
 *Return: dest
 *
 */

char *_strcat(char *dest, char *src)
{
	int d = 0;
	int s = 0;

	while (dest[d] != '\0')
	{
		d++;
	}
	while (src[s] != '\0')
	{
		dest[d] = src[s];
		d++;
		s++;
	}
	dest[d] = '\0';
	return (dest);
}

/**
 * _strcmp - compare the values of a two strings
 * @str1: character1
 * @str2: character2
 * Return: 0
 */

int _strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 > *str2) ? 1 : -1;

		str1++;
		str2++;
	}
	return (*str1 == *str2) ? 0 : ((*str1 > *str2) ? 1 : -1);
}

/**
 *_strncmp -  function that compares two strings.
 *@s1: string one
 *@s2: string two
 *@n: number of characters
 * Return: diference
 */

size_t _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i, j;

	for (j = 0; s1[j] != '\0' && j < n; j++)
	{
		i = s1[j] - s2[j];

		if (i != 0)
		{
			return (i);
		}
	}
	return (0);
}

/**
 * _strcpy - copies the string pointed to by src into dest
 * @dest: destination of the s1
 * @src: source of the s1
 *
 * Return: char pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (*(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		++i;
	}
	*(dest + i) = *(src + i);

	return (dest);
}

/**
 * len_str - Computes the length of a string.
 * @str: A pointer to the string.
 *
 * Return: The length of the string.
 */
int len_str(const char *str)
{
	int i = 0;

	if (!str)
	{
		return (0);
	}

	while (*str++)
		i++;
	return (i);
}

/**
 * stringToInt - converts a string to an integer
 * @str: the input string to be converted
 * Return: the converted integer
 */
int stringToInt(const char *str)
{
	int result = 0;
	int sign = 1;
	int i = 0;

	/*verify the sign*/
	if (str[0] == '-')
	{
		sign = -1;
		i = 1;
	}
	/*convert to integer */
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10 + (str[i] - '0');
		}
		else
		{
			/* if an invalid character exist return 0 */
			return 0;
		}
		i++;
	}

	return sign * result;
}
