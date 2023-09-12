#include "shell.h"

/**
 *_printf - display input
 */

void _printf(const char, *input)
{
	write(STDOUT_FILENO, input, strlen(input));

	return (0);
}			
