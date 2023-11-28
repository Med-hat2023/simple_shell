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
	_eputs(information->fileName);
	_eputs(": ");
	printDecimalToFD(information->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(information->argumentVector[0]);
	_eputs(": ");

	if (errorMessage != NULL)
	{
	_eputs(errorMessage);
	}
	else
	{
	_eputs("Unknown error");
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
	putchar = _eputchar;

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
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
