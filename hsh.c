#include "shell.h"

int shell_loop(char **av, int fd)
{
	ssize_t line = 1;

	while (line != -1)
	{
		char *buffer = malloc(sizeof(char) * BUFFERSIZE);
		if (!buffer)
			return (0);
		size_t buff_size = BUFFERSIZE;
		printf("$ ");
		line = getline(&buffer, &buff_size, stdin);
		if (line == -1) {
			perror("getline: ");
			free(buffer);
			return (0);
		}
		else if (buffer[0] == '\n')
		{
			free (buffer);
			continue;
		}
		buffer[strcspn(buffer, "\n")] = '\0';
		char path[] = "/usr/bin/";

		char *token = strtok(buffer, " ");
		list_t *commad = malloc(sizeof(list_t));
		if (!commad) {
			free(buffer);
			return (0);
		}
		commad->pro = malloc(strlen(path) + strlen(token) + 1);
		if (!commad->pro) {
			free(buffer);
			free(commad);
			return (0);
		}
		strcpy(commad->pro, path);
		strcat(commad->pro, token);

		token = strtok(NULL, " ");
		commad->args = token;
		token = strtok(NULL, " ");
		commad->pathname = token;

		char *args[] = { commad->pro, commad->args, commad->pathname, NULL };
		pid_t pid;
		pid = fork();
		if (pid == -1) {
			perror("Error: ");
			free(buffer);
			free(commad->pro);
			free(commad);
			return (1);
		}
		if (pid == 0) {
			if (execve(args[0], args, NULL) == -1)
				perror("Error: ");
			free(buffer);
			free(commad->pro);
			free(commad);
		} else {
			// Free memory in parent process
			free(buffer);
			free(commad->pro);
			free(commad);
			// Wait for child process to finish
			wait(NULL);
		}
	}
	return (0);
}

