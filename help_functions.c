#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to dest string
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - duplicate string
 * @str: input string
 *
 * Return: pointer to new string
 */

char *_strdup(const char *str)
{
	int length = 0;
	char *new;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	new = malloc(sizeof(char) * (length + 1));

	if (!new)
		return (NULL);

	for (length++; length--;)
		new[length] = *--str;
	return (new);
}

/**
 *_puts - print a string
 *@str: input string
 *
 * Return: void
 */

void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - prints a char
 * @c: input char
 *
 * Return: 1 if success or -1 if error
 */

int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 **_strncpy - copy string
 *@dest: new string
 *@src: source string
 *@n: number of char to copy
 *Return: pointer to copied string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i = 0, j;
	char *new = dest;

	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}

	if (i < n)
	{
		j = i;

		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}

	return (new);
}
