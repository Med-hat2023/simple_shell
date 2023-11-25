#include "shell.h"
#include <unistd.h>
#include <ctype.h>
/**
 * checkInteractiveMode - Check if the shell is in interactive mode.
 *
 * @info: Pointer to the information struct.
 * Return: checkInteractiveMode
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
 * isDelimiter - Check if a character is a delimiter.
 *
 * @character: The character to check.
 * @delimiter: The delimiter string.
 * Return: Returns 1 if the character is a delimiter, 0 otherwise.
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
 *isAlphabetic - Check if a character is an alphabetic character.
 *
 * @character: The character to check.
 * Return: Returns 1 if the character is alphabetic, 0 otherwise.
 */
int isAlphabetic(int character)
{
return (islower(character) || isupper(character) ? 1 : 0);
}



/**
 *stringToIntConverter - Convert a string to an integer.
 *
 * @inputString: The string to be converted.
 * Return:finalResult converted integer if valid,
 *	or 0 if no numbers in the string.
 */
int stringToIntConverter(char *inputString)
{
	int index, signMultiplier = 1, digitFlag = 0, finalResult;
	unsigned int currentResult = 0;

	for (index = 0; inputString[index] != '\0' && digitFlag != 2; index++)
	{
	if (inputString[index] == '-')
	signMultiplier *= -1;

	if (isdigit(inputString[index]))
	{
	digitFlag = 1;
	currentResult *= 10;
	currentResult += (inputString[index] - '0');
	}
	else if (digitFlag == 1)
	digitFlag = 2;
	}

	if (signMultiplier == -1)
	finalResult = -currentResult;
	else
	finalResult = currentResult;

	return (finalResult);
}

