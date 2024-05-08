#include "shell.h"

/**
 * main - entry point
 *
 * @arg_c: arg count
 *
 * @arg_v: arg vector
 *
 * Return: 0 on success, 1 on error
 */

int main(int arg_c, char **arg_v)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (arg_c == 2)
	{
		fd = open(arg_v[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(arg_v[0]);
				_eputs(": 0: Can't open ");
				_eputs(arg_v[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, arg_v);
	return (EXIT_SUCCESS);
}
