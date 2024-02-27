#include "shell.h"
/**
 * _strdup - function that duplicate string
 * @s: the string to suplicate
 * Return: the new duplicated string
 */
char	*_strdup(const char *s)
{
	char	*new_string;
	int		i;

	i = 0;
	new_string = (char *)malloc((_strlen(s) + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	while (s[i])
	{
		new_string[i] = s[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

/**
 * print_env - Prints the current env
 * @env: the env to print
 */
void print_env(char **env)
{
	int x = 0;

	if (env == NULL)
		return;
	while (env[x])
	{
		_puts(env[x]);
		_putchar('\n');
	}
}

/**
 * is_special - checks if the command is special or not
 * @command: the command to check
 * Return: 1 if the command is special, 0 if not
 */
int is_special(char *command)
{
	if (_strncmp(command, "exit", 4) == 0)
	{
		return (1);
	}
	else if (_strncmp(command, "env", 3) == 0)
		return (2);
	else
		return (0);
}

