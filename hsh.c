#include "shell.h"

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
 * free_func - it frees a string
 * @strings: the strings to be freed
 */
void free_func(char **strings)
{
	int i;

	if (strings == NULL)
		return;
	for (i = 0; strings[i] != NULL; ++i)
		free(strings[i]);
	free(strings);
}

/**
 * shell_loop - the shell's main loop
 * @av: arguments
 * @fd: the fd to read from
 * @infs: the struct that has the command infos
 * Return: 1 on Success, 0 otherwise
 */
int shell_loop(char **av, int fd, infs_t *infs)
{
	char **envp = environ;
	ssize_t get = 1;
	int last_command = 0;

	do {
		size_t buffer_int = BUFFER_SIZE;

		infs->buff = NULL;
		infs->buff = malloc(BUFFER_SIZE + 1);
		if (!(infs->buff))
			return (1);
		if (check_term(fd))
			_puts("$ ");
		get = getline(&infs->buff, &buffer_int, stdin);
		if (get == -1)
		{
			if (check_term(fd))
				_putchar('\n');
			free(infs->buff);
			break;
		}
		infs->buff[get - 1] = '\0';
		infs->isBuiltin = is_special(infs->buff);
		last_command = run_command(av, envp, infs);
	} while (get != -1);
	while (wait(NULL) > 0)
		;
	return (last_command);
}
