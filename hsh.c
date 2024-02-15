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
	int status;

	if (child == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			_putserro(av);
			_putserro(": 1: ");
			_putserro(argv[0]);
			_putserro(": not found\n");
			if (errno == EACCES)
				return (2);
			return (127);
		}
	}
	else if (child == -1)
		return (1);
	wait(&status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (-1);
}

/**
 * exec_prog_path - checks if the command exists and execute is
 * @argv: the arguments
 * @av: the program's name
 * Return: 0 Success, 1 Error
 */
int exec_prog_path(char **argv, char *av)
{
	char *full_command_path;
	int i;
	int result;

	full_command_path = does_command_exist(argv[0]);
	if (full_command_path != NULL)
	{
		char **new_argv = (char **)malloc(sizeof(char *) * MAX_ARGS);

		if (!new_argv)
		{
			free(full_command_path);
			return (1);
		}
		new_argv[0] = full_command_path;
		i = 1;
		while (argv[i] != NULL)
		{
			new_argv[i] = argv[i];
			i++;
		}
		new_argv[i] = NULL;
		result = exec_prog(new_argv, av);
		free(full_command_path);
		free(new_argv);
		return (result);
	}
	else
			return (exec_prog(argv, av));
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
	int last_command = 0;

	do {
		size_t buffer_int = BUFFER_SIZE;
		char *token;
		char *argv[1024];
		int i = 0;

		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return (1);
		if (check_term(fd))
			_puts("$ ");
		get = getline(&buff, &buffer_int, stdin);
		if (get == -1)
		{
			if (check_term(fd))
				_putchar('\n');
			free(buff);
			break;
		}
		buff[_strlen(buff) - 1] = '\0';
		token = strtok(buff, " ");
		if (token != NULL)
		{
			while (token != NULL)
			{
				argv[i++] = token;
				token = strtok(NULL, " ");
			}
			argv[i] = NULL;
			last_command = exec_prog_path(argv, av[0]);
		}
		free(buff);
	} while (get != -1);
	while (wait(NULL) > 0)
		;
	return (last_command);
}
