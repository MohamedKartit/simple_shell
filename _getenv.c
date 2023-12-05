#include <stdio.h>
#include <string.h>

extern char **environ;

size_t _strlen(const char *str)
{
	size_t l;

	if (str == NULL)
		return (0);
	l = 0;
	while (str[l])
		l++;
	return (l);
}
char *_getenv(const char *name)
{
	size_t l_name;
	char **env;

	l_name = _strlen(name);
	env = environ;
	while (*env != NULL)
	{
		if (strncmp(name, *env, l_name) == 0 && (*env)[l_name] == '=')
			return (*env + l_name + 1);
		env++;
	}
	return (NULL);
}
int main()
{
	char *var = _getenv("PATH");
	if (var != NULL)
		printf("value of PATH %s\n", var);
	else
		printf("OATH environment not foudn\n");
	return (0);
}
