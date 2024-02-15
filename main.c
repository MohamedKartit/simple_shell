#include "shell.h"

/**
 * main - this is the start of our program
 * @ac: number of arguments
 * @av: the arguments
 * Return: EXIT_SUCCESS on Success, EXIT_FAILURE on failure
 */
int main(int ac, char **av)
{
	int r = 3;

	if (ac == 2)
	{
		r = open(av[1], O_RDONLY);
		if (r == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_putserro(av[0]);
				_putserro(": 0: can't open");
				_putserro(av[1]);
				_putcharerro('\n');
				exit(127);
			}
			return (EXIT_FAILURE);
		}
	}
	return (shell_loop(av, r));
}
