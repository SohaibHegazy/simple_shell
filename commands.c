#include "shell.h"

/**
 * is_exec - determines if a file is executable
 * @info: info structure
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */

int is_exec(info_t *info, char *path)
{
	struct stat st;

	(void)info;

	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
		return (1);

	return (0);
}

/**
 * dup_chars - duplicates characters
 * @path: path string
 * @first: starting index
 * @last: stopping index
 *
 * Return: pointer to new buffer
 */

char *dup_chars(char *path, int first, int last)
{
	static char buf[1024];
	int i = 0, n = 0;

	for (n = 0, i = first; i < last; i++)
		if (path[i] != ':')
			buf[n++] = path[i];
	buf[n] = 0;

	return (buf);
}

/**
 * get_path - gets the path
 * @info: info structure
 * @path: path string
 * @cmd: the cmd to get path for
 *
 * Return: path of cmd or NULL
 */

char *get_path(info_t *info, char *path, char *cmd)
{
	int i = 0, s = 0;
	char *p;

	if (!path)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_exec(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path[i] || path[i] == ':')
		{
			p = dup_chars(path, s, i);

			if (!*p)
				_strcat(p, cmd);
			else
			{
				_strcat(p, "/");
				_strcat(p, cmd);
			}

			if (is_exec(info, p))
				return (p);

			if (!path[i])
				break;
			s = i;
		}
		i++;
	}

	return (NULL);
}

/**
 * chain_str - check if string is a chain
 * @info: info structure
 * @buf: the char buffer
 * @pos: current position
 *
 * Return: 1 if chain, 0 if not
 */

int chain_str(info_t *info, char *buf, size_t *pos)
{
	size_t i = *pos;

	if (buf[i] == '|' && buf[i + 1] == '|')
	{
		buf[i] = 0;
		i++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[i] == '&' && buf[i + 1] == '&')
	{
		buf[i] = 0;
		i++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[i] == ';')
	{
		buf[i] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = i;

	return (1);
}

/**
 * check_chain - checks if to continue chaining
 * @info: info structure
 * @buf: the buffer
 * @pos: position in buf
 * @i: index of buf
 * @len: length of buf
 *
 * Return: Void
 */

void check_chain(info_t *info, char *buf, size_t *pos, size_t i, size_t len)
{
	size_t m = *pos;

	if (info->cmd_buf_type == CMD_AND)
	{

		if (info->status)
		{
			buf[i] = 0;
			m = len;
		}
	}

	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			m = len;
		}
	}

	*pos = m;
}
