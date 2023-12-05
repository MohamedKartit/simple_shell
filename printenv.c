#include <stdio.h>

extern char **environ;
int main(int ac, char *av)
{
	unsigned int x;

	x = 0;
	while (environ[x] != NULL)
		printf("%s\n", environ[x++]);
	return (0);
}
