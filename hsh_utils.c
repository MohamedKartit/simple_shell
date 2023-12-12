#include "shell.h"

/**
 * _strlen - counts the length of a string
 * @s: the string
 * Return: returns the length of the string
 */
int _strlen(char *s)
{
	int len = 0;

	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

/**
 * _strchr - looks for a character in a sting
 * @s: the string
 * @c: the character
 * Return: pointer to the charcter in the string
 */
char *_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *) s);
	return (NULL);
}

