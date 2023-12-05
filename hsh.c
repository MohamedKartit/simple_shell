#include "shell.h"

int check_term(int fd)
{
	return (isatty(STDIN_FILENO) && fd >= 2);
}

int shell_loop(char **av, int fd)
{
	char *buff;
	ssize_t get = 1;
	while (get != -1)
	{
		pid_t child;
		size_t buffer_int = BUFFER_SIZE;
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return (0);
		if (check_term(fd))
			_puts("$ ");
		get = getline(&buff, &buffer_int, stdin);
		if (get == -1)
		{
			if (check_term(fd))
				_putchar('\n');
			free(buff);
			return (1);
		}
		buff[strcspn(buff, "\n")] = '\0';
		char *token = strtok(buff, " ");
		if (token == NULL)
		{
			free(buff);
			continue;
		}

		char *argv[10];
		int i = 0;
		while (token != NULL)
		{
			argv[i++] = token;
			token = strtok(NULL, " ");
		}
		argv[i] = NULL;
		child = fork();
		if (child == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
			{
				_puts(av[0]);
				_puts(": No such file or directory\n");
				free(buff);
				return EXIT_FAILURE;
			}
		}
		else if (child == -1)
		{
			perror("fork");
			free(buff);
			return 1;
		}
		else
		{
			free(buff);
			wait(NULL);
			buff = NULL;
		}
	}
	free(buff);
	return (0);
}
