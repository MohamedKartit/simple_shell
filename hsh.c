#include "shell.h"

/**
 * exec_prog - the exec function that execute the command
 * @argv: the arguments
 * @av: the program's name
 * Return: 0 Success, 1 Error
 */
int exec_prog(char **argv, char *av)
{
	pid_t child = fork();

	if (child == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			_puts(av);
			_puts(": No such file or directory\n");
			return (1);
		}
	}
	else if (child == -1)
		return (1);
	wait(NULL);
	return (0);
}

/**
 * check_term - check if the command is from terminal
 * @fd: the fd to read from
 * Return: 1 if it's reading from terminal 0 if it's not
 */
int check_term(int fd)
{
	return (isatty(STDIN_FILENO) && fd >= 2);
}

/**
 * shell_loop - the shell's main loop
 * @av: arguments
 * @fd: the fd to read from
 * Return: 1 on Success, 0 otherwise
 */
int shell_loop(char **av, int fd)
{
	char *buff;
	ssize_t get = 1;

	while (get != -1)
	{
		size_t buffer_int = BUFFER_SIZE;
		char *token;
		char *argv[1024];
		int i = 0;

		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return (EXIT_FAILURE);
		if (check_term(fd))
			_puts("$ ");
		get = getline(&buff, &buffer_int, stdin);
		if (get == -1)
		{
			if (check_term(fd))
				_putchar('\n');
			free(buff);
			return (EXIT_FAILURE);
		}
		buff[_strlen(buff) - 1] = '\0';
		token =	strtok(buff, " ");
		if (token != NULL)
		{
			while (token != NULL)
			{
				argv[i++] = token;
				token = strtok(NULL, " ");
			}
			argv[i] = NULL;
			if (exec_prog(argv, av[0]) == 1)
				return (free(buff), EXIT_FAILURE);
		}
		free(buff);
	}
	free(buff);
	return (EXIT_SUCCESS);
}
