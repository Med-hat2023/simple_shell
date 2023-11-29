#include "shell.h"

#include <limits.h>


/**
 * convertStringToInt - converts a string to an integer
 * @inputString: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *	-1 on error
 */
int convertStringToInt(char *inputString)
{
	int is_negative = 0;
	unsigned long int converted_number = 0;

	if (*inputString == '+')
	inputString++;

	for (is_negative = 0; inputString[is_negative] != '\0'; is_negative++)
	{
	if (inputString[is_negative] >= '0' && inputString[is_negative] <= '9')
	{
	converted_number *= 10;
	converted_number += (inputString[is_negative] - '0');

	if (converted_number > 9999)
	return (-1);
	}
	else
	{
	return (-1);
	}
	}

	return (converted_number);
}

/**
 * displayErrorInfo - outputs an error message along with relevant information
 * @information: the parameter & return info struct
 * @errorMessage: string containing specified error type
 * Returns: N/A
 */
void displayErrorInfo(info_t *information, char *errorMessage)
{
	printText(information->fileName);
	printText(": ");
	printDecimalToFD(information->line_count, STDERR_FILENO);
	printText(": ");
	printText(information->argumentVector[0]);
	printText(": ");

	if (errorMessage != NULL)
	{
	printText(errorMessage);
	}
	else
	{
	printText("Unknown error");
	}

}


/**
 * printDecimalToFD - outputs a decimal (integer)
 * number (base 10) to a file descriptor
 * @value: the input value to be printed
 * @fileDescriptor: the file descriptor to write to
 * Return: number of characters printed
 */
int printDecimalToFD(int value, int fileDescriptor)
{
	int (*putchar)(char) = putchar;
	int occurrences = 0;

	unsigned int absoluteValue = (value < 0) ? -value : value;
	int curValue = absoluteValue;
	int y = 100000 * 10000;	/*Move the declaration and initialization of y here*/
	int digit = curValue / y;

	if (fileDescriptor == STDERR_FILENO)
	putchar = writeToStderr;

	if (value < 0)
	{
	putchar('-');
	occurrences++;
	}

	while (y > 1)
	{
	if (digit)
	{
	putchar('0' + digit);
	occurrences++;
	}
	curValue %= y;
	y /= 10;
	}

	putchar('0' + curValue);
	occurrences++;

	return (occurrences);
}


/**
 * numberToString - brief Converts a number to a string
 * representation in the specified base.
 *
 * @number: The number to be converted.
 * @initialBase: The initial base for the conversion.
 * @conversionFlags: Flags for special conversion options.
 *	Use CONVERT_UNSIGNED flag for unsigned conversion.
 *	Use CONVERT_LOWER flag for lowercase hex characters.
 * Return: A string representation of the converted number.
 */
char *numberToString(long int number, int initialBase, int conversionFlags)
{
	static char *characterSet;
	static char resultBuffer[60];
	char direction = 0;
	/* Changed variable name from 'resultPtr' to 'resultPointer'*/
	char *resultPointer;
	unsigned long n = (unsigned long)number;

	if (!(conversionFlags & CONVERT_UNSIGNED) && number < 0)
	{
	n = -number;
	direction = '-';
	}

	characterSet = (conversionFlags & lowercaseConversion) ?
		"0123456789abcdef" : "0123456789ABCDEF";
	/* Changed variable name from 'resultPtr' to 'resultPointer'*/
	resultPointer = &resultBuffer[59];
	*resultPointer = '\0';

	for (; n != 0; n /= initialBase)
	{
	/*Changed variable name from 'base' to 'initialBase'*/
		*--resultPointer = characterSet[n % initialBase];
	}

	if (direction)
	*--resultPointer = direction;

	return (resultPointer);
}

/**
 * deactivateHash - Removes the first '#' occurrence in the given string.
 * @inputString: Pointer to the string to be modified.
 *
 * This function employs a do-while loop to locate and replace
 * the first '#' character
 * with '\0' if it is either at the beginning of the string or follows a space.
 *
 * Return: in this cases Always (0).
 */
void deactivateHash(char *inputString)
{
	int index = 0;

	do {
	if (inputString[index] == '#' && (index == 0 ||
				inputString[index - 1] == ' '))
	{
	inputString[index] = '\0';
	break;
	}
	index++;
	} while (inputString[index] != '\0');
}

