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
		x++;
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
		return (1);
	else if (_strncmp(command, "env", 3) == 0)
		return (2);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _atoi(char *s)
{
	int i = 0;
	unsigned long int number = 0;

	if (*s == '+')
		s++;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			number = number * 10 + (s[i] - '0');
			if (number > INT_MAX)
				return (-1);
		}
		else
			return (-1);
		i++;
	}
	return (number);
}

/**
 * exit_func - do the exit builtins
 * @infs: the truct that has infos about the command
 * @av: the argv
 * Return: returns status
 */
int exit_func(infs_t *infs, char **av)
{
	int num;

	if (infs->cmd_args[1])
	{
		num = _atoi(infs->cmd_args[1]);
		if (num == -1)
		{
			_putserro(av[0]);
			_putserro(": 1: exit: Illegal number: ");
			_putserro(infs->cmd_args[1]);
			_putcharerro('\n');
			flush_infs(infs);
			return (2);
		}
		free_func(infs->cmd_args);
		free(infs->buff);
		exit(num);
	}
	free_func(infs->cmd_args);
	free(infs->buff);
	exit(infs->status);
}

