#include "shell.h"

/**
 * add_node_end - add node to end of list
 * @head: pointer to head
 * @str: string on a node
 * @num: node index
 *
 * Return: size of list
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));

	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints str element of list_t
 * @h: pointer to first node
 *
 * Return: size of list
 */

size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}

	return (i);
}

/**
 * free_list - frees nodes of list
 * @head_ptr: pointer to head
 *
 * Return: void
 */

void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;

	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

/**
 * list_strings - makes array of strings for list->str
 * @h: pointer to head
 *
 * Return: array of strings
 */

char **list_strings(list_t *h)
{
	list_t *node = h;
	size_t i = list_len(h), j;
	char **str_arr;
	char *str;

	if (!h || !i)
		return (NULL);

	str_arr = malloc(sizeof(char *) * (i + 1));
	if (!str_arr)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(str_arr[j]);
			free(str_arr);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		str_arr[i] = str;
	}
	str_arr[i] = NULL;

	return (str_arr);
}

/**
 * list_len - get length of list
 * @h: pointer to head
 *
 * Return: size of list
 */

size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}
