#include "shell.h"

/**
 * _memset - fill bytes with a constant
 * @str: pointer to string
 * @c: character to be filled with
 * @n: number of times to use c
 *
 * Return: pointer to str
 */

char *_memset(char *str, char c, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		str[i] = c;
	return (str);
}

/**
 * free_arr - free array of strings
 * @ptr: array of strings
 *
 * Return: void
 */

void free_arr(char **ptr)
{
	char **a = ptr;

	if (!ptr)
		return;

	while (*ptr)
		free(*ptr++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloced block
 * @old_size: size of previous block
 * @new_size: size of new block
 *
 * Return: void
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
		return (free(ptr), NULL);

	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);

	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;

	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];

	free(ptr);
	return (p);
}

/**
 * set_free - free pointer and assign NULL
 * @ptr: the pointer
 *
 * Return: 1 if success or 0 if failed
 */

int set_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
