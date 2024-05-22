#include "shell.h"

/**
 * input_buf - buffers chained commands
 *
 * @info: parameter struct
 *
 * @buf: address of buffer
 *
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t read = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		read = getline(buf, &len_p, stdin);
#else
		read = _getline(info, buf, &len_p);
#endif
		if (read > 0)
		{
			if ((*buf)[read - 1] == '\n')
			{
				(*buf)[read - 1] = '\0'; /* remove trailing newline */
				read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = read;
				info->cmd_buf = buf;
			}
		}
	}
	return (read);
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
	static size_t a, b, len;
	ssize_t read = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	read = input_buf(info, &buf, &len);
	if (read == -1)
		return (-1);
	if (len)
	{
		b = a; /* init new iterator to current buf position */
		p = buf + a; /* get pointer for return */

		check_chain(info, buf, &b, a, len);
		while (b < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &b))
				break;
			b++;
		}

		a = b + 1; /* increment past nulled ';'' */
		if (a >= len) /* reached end of buffer? */
		{
			b = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (read); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *a)
{
	ssize_t rd = 0;

	if (*a)
		return (0);
	rd = read(info->readfd, buf, READ_BUF_SIZE);
	if (rd >= 0)
		*a = rd;
	return (rd);
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
	static size_t a, len;
	size_t c;
	ssize_t read = 0, s = 0;
	char *p = NULL, *new_p = NULL, *d;

	p = *ptr;
	if (p && length)
		s = *length;
	if (a == len)
		a = len = 0;

	read = read_buf(info, buf, &len);
	if (read == -1 || (read == 0 && len == 0))
		return (-1);

	c = _strchr(buf + a, '\n');
	c = d ? 1 + (unsigned int)(d - buf) : len;
	new_p = _realloc(p, s, s ? s + c : c + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + a, c - a);
	else
		_strncpy(new_p, buf + a, c - a + 1);

	s += c - a;
	a = c;
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
	_putchar(BUF_FLUSH);
}
