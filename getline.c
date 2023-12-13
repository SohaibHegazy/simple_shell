#include "shell.h"

/**
 * buf_cmd - get command line into a buffer
 * @info: info structure
 * @buf: buffer
 * @len: size
 *
 * Return: bytes read
 */

ssize_t buf_cmd(info_t *info, char **buf, size_t *len)
{
	ssize_t bytes = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		bytes = _getline(info, buf, &len_p);

		if (bytes > 0)
		{
			if ((*buf)[bytes - 1] == '\n')
			{
				(*buf)[bytes - 1] = '\0';
				bytes--;
			}
			info->linecount_flag = 1;
			*len = bytes;
			info->cmd_buf = buf;
		}
	}

	return (bytes);
}

/**
 * input_cmd - get the input
 * @info: info structure
 *
 * Return: bytes read
 */

ssize_t input_cmd(info_t *info)
{
	static char *buf;
	static size_t len;
	ssize_t bytes = 0;
	char **buf_p = &(info->arg);
	static size_t i, j;
	char *p;

	_putchar(BUF_FLUSH);
	bytes = buf_cmd(info, &buf, &len);

	if (bytes == -1)
		return (-1);

	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (chain_str(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (bytes);
}

/**
 * get_buf - read the buffer
 * @info: info structure
 * @buf: buffer
 * @size: size of buffer
 *
 * Return: bytes read
 */

ssize_t get_buf(info_t *info, char *buf, size_t *size)
{
	ssize_t bytes = 0;

	if (*size)
		return (0);
	bytes = read(info->readfd, buf, READ_BUF_SIZE);
	if (bytes >= 0)
		*size = bytes;
	return (bytes);
}

/**
 * _getline - replaces getline to get from stdin
 * @info: info structure
 * @ptr: pointer to buffer
 * @length: size of buffer
 *
 * Return: bytes read
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t m;
	ssize_t r = 0, bytes = 0;
	char *p = NULL, *new = NULL, *c;

	p = *ptr;
	if (p && length)
		bytes = *length;
	if (i == len)
		i = len = 0;

	r = get_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	m = c ? 1 + (unsigned int)(c - buf) : len;
	new = _realloc(p, bytes, bytes ? bytes + m : m + 1);
	if (!new)
		return (p ? free(p), -1 : -1);

	if (bytes)
		_strncat(new, buf + i, m - i);
	else
		_strncpy(new, buf + i, m - i + 1);

	bytes += m - i;
	i = m;
	p = new;

	if (length)
		*length = bytes;
	*ptr = p;
	return (bytes);
}



/**
 * sigintHandler - block the ctrl-C signal
 * @sig_num: signal number
 *
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
