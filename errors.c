#include "shell.h"

/**
 * _eputs - prints an input string
 *
 * @s: the string to be printed
 *
 * Return: Nothing
 */

void _eputs(char *s)
{
	int a = 0;

	if (!s)
		return;
	while (s[a] != '\0')
	{
		_eputchar(s[a]);
		a++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 *
 * @c: The character to print
 *
 * Return: 1 on success or -1 and set errno appropriately.
 */

int _eputchar(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 *
 * @c: The character to print
 *
 * @fd: The filedescriptor to write to
 *
 * Return: 1 on success, or -1 and set errno appropriately.
 */

int _putfd(char c, int fd)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}

/**
 * _putsfd - prints an input string
 *
 * @str: the string to be printed
 *
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */

int _putsfd(char *s, int fd)
{
	int a = 0;

	if (!s)
		return (0);
	while (*s)
	{
		a += _putfd(*s++, fd);
	}
	return (a);
}
