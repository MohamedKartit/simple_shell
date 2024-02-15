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
 * does_command_exist - checks if the command exists in the PATH
 * @command: the command
 * Return: Returns the full path of the command or NULL
 */

char *does_command_exist(const char *command)
{
	char *path = get_full_path();
	char *dir;
	char *command_path = NULL;
	struct stat st;

	if (path == NULL)
		return (NULL);
	dir = strtok(path, ":");
	while (dir != NULL)
	{
		command_path = (char *)malloc(sizeof(char) * BUFFER_SIZE);
		if (!command_path)
		{
			free(path);
			return (NULL);
		}
		_strlcpy(command_path, dir, BUFFER_SIZE);
		_strlcat(command_path, "/", BUFFER_SIZE);
		_strlcat(command_path, command, BUFFER_SIZE);
		if (stat(command_path, &st) == 0)
		{
			free(path);
			return (command_path);
		}
		free(command_path);
		dir = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}

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
