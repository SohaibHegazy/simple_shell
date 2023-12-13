#include "shell.h"

/**
 * interactive - check interactive mode
 * @info: info structure
 *
 * Return: 1 if interactive mode or 0 if uninteractive
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is delimeter
 * @c: input char
 * @delim: delimeter string
 * Return: 1 if delim or 0 if not
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @c: input char
 *
 * Return: 1 if alphabetic or 0 if not
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - convert string to integer
 * @s: input string
 *
 * Return: 0 if no number or the number converted
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int res = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -res;
	else
		output = res;

	return (output);
}

/**
 * **strtow - convert string to words.
 * @st: input string
 * @delim: delimeter string
 * Return: pointer to array of strings or NULL if failed
 */

char **strtow(char *st, char *delim)
{
	int i, j, k, m, n = 0;
	char **s;

	if (st == NULL || st[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; st[i] != '\0'; i++)
		if (!is_delim(st[i], delim) && (is_delim(st[i + 1], delim) || !st[i + 1]))
			n++;

	if (n == 0)
		return (NULL);
	s = malloc((1 + n) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < n; j++)
	{
		while (is_delim(st[i], delim))
			i++;
		k = 0;
		while (!is_delim(st[i + k], delim) && st[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = st[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
