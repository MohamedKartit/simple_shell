#include "shell.h"

int main(int ac, char **av)
{
	int r = 3;
	if (ac == 2)
	{
		r = open(av[1], O_RDONLY);
		if (r == -1)
		{
			_puts(av[0]);
			_puts(": 0: can't open");
			_puts(av[1]);
			_putchar('\n');
			return (EXIT_FAILURE);
		}
	}
	shell_loop(av, r);
	return EXIT_SUCCESS;
}
