#include "shell.h"

/**
 * err_atoi - string to integer for errors
 * @str: string
 *
 * Return: 0 if no numbers or the number or -1 if error
 */

int err_atoi(char *str)
{
	int i = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;

	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			res *= 10;
			res += (str[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (res);
}

/**
 * err_print - print error message
 * @info: info structure
 * @err_str: string with error type
 *
 * Return: void
 */

void err_print(info_t *info, char *err_str)
{
	err_puts(info->fname);
	err_puts(": ");
	dec_print(info->line_count, STDERR_FILENO);
	err_puts(": ");
	err_puts(info->argv[0]);
	err_puts(": ");
	err_puts(err_str);
}

/**
 * dec_print - print decimal number
 * @n: input number
 * @fd: file descriptor
 *
 * Return: bytes printed
 */

int dec_print(int n, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, bytes = 0;
	unsigned int abs, current;

	if (fd == STDERR_FILENO)
		__putchar = err_putchar;
	if (n < 0)
	{
		abs = -n;
		__putchar('-');
		bytes++;
	}
	else
		abs = n;

	current = abs;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs / i)
		{
			__putchar('0' + current / i);
			bytes++;
		}
		current %= i;
	}
	__putchar('0' + current);
	bytes++;

	return (bytes);
}

/**
 * err_puts - puts for error
 * @str: input string to print
 *
 * Return: void
 */

void err_puts(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		err_putchar(str[i]);
		i++;
	}
}

/**
 * err_putchar - prints char to stderr
 * @ch: The character to print
 *
 * Return: 1 if success
 */

int err_putchar(char ch)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}

	if (ch != BUF_FLUSH)
		buf[i++] = ch;

	return (1);
}
