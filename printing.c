#include "shell.h"

/**
 * _putchar - print charcter
 * @c: the character
 * Return: 1 succss, -1 error
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - prints a string
 * @str: the string
 * Return: number of charcter printed
 */
int _puts(char *str)
{
	int x = 0;

	if (!str)
		return (0);
	while (str[x])
		_putchar(str[x++]);
	return (x);
}

/**
 * _putcharerro - print char in the stderr
 * @c: the character
 * Return: returns 1 if printed -1 error
 */
int _putcharerro(char c)
{
	return (write(2, &c, 1));
}

/**
 * _putserro - print string in the stderr
 * @str: the string to be printed
 * Return: number of charcter printed
 */
int _putserro(char *str)
{
	int x = 0;

	if (!str)
		return (0);
	while (str[x])
		_putcharerro(str[x++]);
	return (x);
}

