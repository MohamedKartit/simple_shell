#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>

# define BUFFER_SIZE 1024
int main()
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
		printf("$ ");
		get = getline(&buff, &buffer_int, stdin);
		if (get == -1)
		{
			printf("here\n");
			free(buff);
			return (1);
		}
		buff[strcspn(buff, "\n")] = '\0';
		char *argv[] = {buff, NULL};
		child = fork();
		if (child == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("execve:");
				return EXIT_FAILURE;
			}
		}
		else
		{
			free(buff);
			wait(NULL);
		}
	}
	free(buff);
	return (0);
}

