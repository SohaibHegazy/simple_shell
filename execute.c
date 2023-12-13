#include "shell.h"

/**
 * shell_loop - main shell loop
 * @info: info structure
 * @av: argument vector
 *
 * Return: 0 if success or error code
 */

int shell_loop(info_t *info, char **av)
{
	ssize_t r = 0;
	int b = 0;

	while (r != -1 && b != -2)
	{
		info_init(info);
		if (interactive(info))
			_puts("$ ");
		err_putchar(BUF_FLUSH);
		r = input_cmd(info);
		if (r != -1)
		{
			info_t_put(info, av);
			b = check_builtin(info);
			if (b == -1)
				cmd_path(info);
		}
		else if (interactive(info))
			_putchar('\n');
		info_t_free(info, 0);
	}
	info_t_free(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (b == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (b);
}

/**
 * check_builtin - checks builtin commands
 * @info: info sructure
 *
 * Return: -1 no built-in or 0 if executed or
 * -2 if signals exit or 1 if found not exec
 */

int check_builtin(info_t *info)
{
	int i, b = -1;
	builtin_table btable[] = {
		{"exit", builtin_exit},
		{"env", _env},
		{NULL, NULL}
	};

	for (i = 0; btable[i].type; i++)
		if (_strcmp(info->argv[0], btable[i].type) == 0)
		{
			info->line_count++;
			b = btable[i].func(info);
			break;
		}

	return (b);
}

/**
 * cmd_path - finds a command in path
 * @info: info structure
 *
 * Return: void
 */

void cmd_path(info_t *info)
{
	char *path = NULL;
	int i, m;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, m = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			m++;
	if (!m)
		return;

	path = get_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_exec(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_exec(info, info->argv[0]))
			fork_exec(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			err_print(info, "not found\n");
		}
	}
}

/**
 * fork_exec - creates process to execute using execve
 * @info: info structure
 *
 * Return: void
 */

void fork_exec(info_t *info)
{
	pid_t ch_pid;

	ch_pid = fork();
	if (ch_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (ch_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			info_t_free(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				err_print(info, "Permission denied\n");
		}
	}
}
