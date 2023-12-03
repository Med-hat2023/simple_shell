#include "shell.h"

/**
 * fetch_input_commands - into a buffer, updating information.
 *
 * @data: Pointer to the parameter struct.
 * @buffer: Address of the buffer to store input commands.
 * @length_pointer: Address of the length variable for the buffer.
 * Return: The number of bytes read.
 */
ssize_t fetch_input_commands(info_t *data, char **buffer,
		size_t *length_pointer)
{
	ssize_t bytesRead = 0;
	size_t lengthPointer = 0;

	if (!(*length_pointer)) /* if nothing left in the buffer, fill it */
	{
	/*bfree((void **)data->cmd_buf);*/
	free(*buffer);
	*buffer = NULL;
	signal(SIGINT, sigintHandler);

#if USE_GET_LINE
	bytesRead = getline(buffer, &lengthPointer, stdin);
#else
	bytesRead = _getline(data, buffer, &lengthPointer);
#endif

	if (bytesRead > 0)
	{
	if ((*buffer)[bytesRead - 1] == '\n')
	{
	(*buffer)[bytesRead - 1] = '\0'; /* remove trailing newline */
	bytesRead--;
	}

	data->linecount_flag = 1;
	deactivateHash(*buffer);
	build_history_list(data, *buffer, data->histcount++);
	if (strchr(*buffer, ';'))
	{
	*length_pointer = bytesRead;
	data->cmd_buf = buffer;
	}
	else
	{
	*length_pointer = bytesRead;
	}
	}
	}
return (bytesRead);
}

/**
* get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->argumentCount), *p;

	_putchar(CLEAR_BUFFER);
	r = fetch_input_commands(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = FindCharacter(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		ConcatenateLimited(new_p, buf + i, k - i);
	else
		CustomStringCopy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(CLEAR_BUFFER);
}
