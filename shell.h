#ifndef _SHELL_H_
#define _SHELL_H_

/*========== LIBRARIES ==========*/

#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/*========== CONSTS ==========*/

#define BUFFER_SIZE 1024
#define MAX_ARGS 20

extern char **environ;

/*========== PRINTING ==========*/

int _putchar(char c);
int _putcharerro(char c);
int _puts(char *str);
int _putserro(char *str);

int	_strncmp(const char *s1, const char *s2, size_t n);
char *_strchr(char *s, int c);
int _strlen(const char *s);
int exec_prog(char **argv, char *av);
int shell_loop(char **av, int fd);
char *does_command_exist(const char *command);
int exec_prog_path(char **argv, char *av);
size_t	_strlcat(char *dst, const char *src, size_t size);
size_t	_strlcpy(char *dst, const char *src, size_t size);
char *get_full_path();
char	*_strdup(const char *s);
int is_special(char *command);
void print_env(char **env);

#endif
