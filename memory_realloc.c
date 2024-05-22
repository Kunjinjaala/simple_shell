#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 *
 * @m: the pointer to the memory area
 *
 * @n: the byte to fill *s with
 *
 * @o: the amount of bytes to be filled
 *
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *m, char n, unsigned int o)
{
	unsigned int a;

	for (a = 0; a < o; a++)
		m[a] = n;
	return (m);
}

/**
 * ffree - frees a string of strings
 *
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **b = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(b);
}

/**
 * _realloc - reallocates a block of memory
 *
 * @ptr: pointer to previous malloc'ated block
 *
 * @old_size: byte size of previous block
 *
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
