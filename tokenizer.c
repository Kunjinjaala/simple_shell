#include "shell.h"

/**
 * **str_to_two - splits a string into words. Repeat delimiters are ignored
 *
 * @str: the input string
 *
 * @delm: the delimeter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **str_to_two(char *str, char *delm)
{
	int a, b, c, d, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delm)
		delm = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!_isdelim(str[a], delm) && (_isdelim(str[a + 1], delm) || !str[a + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (_isdelim(str[a], delm))
			a++;
		c = 0;
		while (!_isdelim(str[a + c], delm) && str[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			s[b][d] = str[a++];
		s[b][d] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **str_to_two2 - splits a string into words
 * @str: the input string
 *
 * @delm: the delimeter
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **str_to_two2(char *str, char delm)
{
	int a, b, c, d, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != delm && str[a + 1] == delm) ||
				    (str[a] != delm && !str[a + 1]) || str[a + 1] == delm)
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (str[a] == delm && str[a] != delm)
			a++;
		c = 0;
		while (str[a + c] != delm && str[a + c] && str[a + c] != delm)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			s[b][d] = str[a++];
		s[b][d] = 0;
	}
	s[b] = NULL;
	return (s);
}
