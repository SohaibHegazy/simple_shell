#include "shell.h"

/**
 * info_init - initializes info_t struct
 * @info: info structure
 *
 * Return: void
 */

void info_init(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * info_t_put - add info to info_t structure
 * @info: info structure
 * @av: arg vector
 *
 * Return: void
 */

void info_t_put(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}

		for (i = 0; info->argv && info->argv[i]; i++)
			;

		info->argc = i;
	}
}

/**
 * info_t_free - free info_t structure parameters
 * @info: struct address
 * @done: true if freeing all fields
 *
 * Return: void
 */

void info_t_free(info_t *info, int done)
{
	free_arr(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (done)
	{
		if (!info->cmd_buf)
			free(info->arg);

		if (info->env)
			free_list(&(info->env));

		free_arr(info->environ);
			info->environ = NULL;

		set_free((void **)info->cmd_buf);

		if (info->readfd > 2)
			close(info->readfd);

		_putchar(BUF_FLUSH);
	}
}

/**
 * _strchr - get char location
 * @str: input string
 * @c: character to locate
 *
 * Return: pointer to location
 */

char *_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
