#include "shell.h"
#include <unistd.h>

/**
 * checkInteractiveMode - Check if the shell is in interactive mode.
 *
 * @info: Pointer to the information struct.
 * isInteractiveMode: Return: checkInteractiveMode
 */

int checkInteractiveMode(info_t *info)
{
	/* Step 1: Check if stdin is associated with a terminal*/
int isStdinTerminal = isatty(STDIN_FILENO);

	/* Step 2: Check if readfd is less than or equal to 2*/
int isReadfdValid = info->readfd <= 2;

	/* Step 3: Combine the results of Step 1 and Step 2*/
int isInteractiveMode = isStdinTerminal && isReadfdValid;

	/* Step 4: Return the final result*/
return (isInteractiveMode);
}



/**
 * Check if a character is a delimiter.
 *
 * @character The character to check.
 * @delimiter The delimiter string.
 * return: Returns 1 if the character is a delimiter, 0 otherwise.
 */
int isDelimiter(char character, char *delimiter) 
{
    do {
        if (*delimiter == character) 
	{
            return (1); /* Character is a delimiter */
        }
    } while (*delimiter++);

    return (0); /* Character is not a delimiter */
}

/**
 *_isalpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;	s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
