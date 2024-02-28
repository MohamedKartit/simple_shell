#include "shell.h"

/**
 * _strjoin - it joins 2 strings togther
 * @s1: the first string
 * @s2: the second string
 * Return: the concate of the 2 string
 */
char	*_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*ptr;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (_strdup(s2));
	if (!s2)
		return (_strdup(s1));
	str = (char *)malloc(sizeof(char) * (_strlen(s1) + _strlen(s2) + 1));
	if (!str)
		return (NULL);
	ptr = str;
	while (*s1 != '\0' && s1)
		*ptr++ = *s1++;
	while (*s2 != '\0' && s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (str);
}

/**
 * error_printer - prints an error message
 * @infs: the parameter & return infs struct
 * @av: the argv
 * @str: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void error_printer(infs_t *infs, char **av, char *str)
{
	_putserro(av[0]);
	_putserro(": 1: ");
	_putserro(infs->cmd_args[0]);
	_putserro(str);
}

/**
 * flush_infs - this fucntion flush teh struct
 * @infs: the struct to be flushed
 */
void flush_infs(infs_t *infs)
{
	free_func(infs->cmd_args);
	free_func(infs->paths);
	if (infs->cmd)
		free(infs->cmd);
	if  (infs->buff)
		free(infs->buff);
}

