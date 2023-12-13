#include "shell.h"

/**
 * _strlen - get length of string
 * @s: input string
 *
 * Return: length
 */

int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - compare two strangs.
 * @s1: first input string
 * @s2: second input string
 *
 * Return: -ve if s1 < s2 or +ve if s1 > s2 or 0 if s1 == s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: input string
 * @needle: string to find
 *
 * Return: address of next char of haystack or NULL
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: final concatenated string
 * @src: source string
 *
 * Return: pointer to dest
 */
char *_strcat(char *dest, char *src)
{
	char *cat = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;

	return (cat);
}

/**
 * _strncat - concatenate n chars of a string to another strings
 * @dest: final string
 * @src: source string
 * @n: bytes to copy
 *
 * Return: dest string
 */

char *_strncat(char *dest, char *src, int n)
{
	int i = 0, j = 0;
	char *cat = dest;

	while (dest[i] != '\0')
		i++;

	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	if (j < n)
		dest[i] = '\0';

	return (cat);
}
