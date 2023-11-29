#include "shell.h"

/**
 * printText - Outputs characters from a given string.
 * @text: The string to be printed.
 *
 * This function uses a do-while loop to print
 * each character of the input string
 * using a custom printing function (_eputchar).
 * If the input string is NULL, the
 * function returns without performing any action.
 *@text:refers to print str
 * Return: No anY things
 */
void printText(char *text)
{
	int index = 0;

	if (!text)
	return;

	do {
	writeToStderr(text[index]);
	index++;
	} while (text[index] != '\0');
}

/**
 * writeToStderr - Outputs a character to the standard error stream.
 * @outputChar: The character to be written.
 *
 * This function writes the given character to the standard error stream.
 * If the character is BUF_FLUSH or the internal buffer is full, the buffer
 * is flushed to stderr. On success, it returns 1; on error, -1 is returned,
 * and errno is set appropriately.
 * Return:	On success, it returns 1; on error, -1 is returned,
 */
int writeToStderr(char outputChar)
{
	static int bufferIndex;
	/*Change this value as needed*/

	static char writeBuffer[ADJUSTABLE_WRITE_BUFFER_SIZE];

	if (outputChar == CLEAR_BUFFER || bufferIndex >=
			ADJUSTABLE_WRITE_BUFFER_SIZE)
	{
	write(2, writeBuffer, bufferIndex);
	bufferIndex = 0;
	}
	else
	{
	writeBuffer[bufferIndex++] = outputChar;
	}

	return (1);
}

/**
 * writeToDescriptor - Sends a character to the specified file descriptor.
 * @outputChar: The character to be transmitted.
 * @fileDescriptor: The file descriptor to write to.
 *
 * This function writes the provided character to
 * the specified file descriptor.
 * If the character is CLEAR_BUFFER or the internal
 * buffer is full, the buffer
 * is flushed to the file descriptor. On success, it returns 1; on error, -1 is
 * returned, and errno is set appropriately.
 * Return: 1 on error
 */
int writeToDescriptor(char outputChar, int fileDescriptor)
{
	static int bufferIndex;
	static char writeBuffer[ADJUSTABLE_WRITE_BUFFER_SIZE];
	 /* Change this character as needed*/

	if (outputChar == CLEAR_BUFFER)
	{
	write(fileDescriptor, writeBuffer, bufferIndex);
	bufferIndex = 0;
	}
	else if
		(bufferIndex >= ADJUSTABLE_WRITE_BUFFER_SIZE)
		{
	write(fileDescriptor, writeBuffer, bufferIndex);
	bufferIndex = 0;
	}
	else
	{
	writeBuffer[bufferIndex++] = outputChar;
	}

	return (1);
}


/**
 *_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += writeToDescriptor(*str++, fd);
	}
	return (i);
}
