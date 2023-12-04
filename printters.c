#include "shell.h"

int _putchar(char c)
{
	return (write(1, &c, 1));
}

int _puts(char *str)
{
	int x = 0;
	if (!str)
		return 0;
	while (str[x])
		_putchar(str[x++]);
	return (x);
}

