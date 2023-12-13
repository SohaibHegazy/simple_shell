#include "shell.h"

/**
 * builtin_exit - exits the shell
 * @info: info structure
 *
 * Return: exits the shell
 */

int builtin_exit(info_t *info)
{
	int check;

	if (info->argv[1])
	{
		check = err_atoi(info->argv[1]);

		if (check == -1)
		{
			info->status = 2;
			err_print(info, "Illegal number: ");
			err_puts(info->argv[1]);
			err_putchar('\n');
			return (1);
		}
		info->err_num = err_atoi(info->argv[1]);

		return (-2);
	}
	info->err_num = -1;

	return (-2);
}

