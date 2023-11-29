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

	static char writeBuffer[ADJUSTABLE_WRITE_BUFFER_SIZE];

	if (outputChar == BUF_FLUSH || bufferIndex >=
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
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[ADJUSTABLE_WRITE_BUFFER_SIZE];

	if (c == BUF_FLUSH || i >= ADJUSTABLE_WRITE_BUFFER_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
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
		i += _putfd(*str++, fd);
	}
	return (i);
}
