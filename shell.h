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
#define INF_INITIALIZER {NULL, NULL, NULL}
extern char **environ;

/**
 * struct infs_s - This struct have infos about the entred command
 * @cmd: the command
 * @paths: the available paths
 * @cmd_args: the command and its paths
 */
typedef struct infs_s
{
	char *cmd;
	char **paths;
	char **cmd_args;
} infs_t;

/*========== PRINTING ==========*/

int _putchar(char c);
int _putcharerro(char c);
int _puts(char *str);
int _putserro(char *str);
void error_printer(infs_t *infs, char **av, char *str);

/*========= PARSING ============*/
char *_strjoin(char const *s1, char const *s2);
int	_strncmp(const char *s1, const char *s2, size_t n);
char *_strchr(char *s, int c);
int _strlen(const char *s);
char	**_strtok(char const *s, char c);

size_t	_strlcat(char *dst, const char *src, size_t size);
size_t	_strlcpy(char *dst, const char *src, size_t size);
char	*_strdup(const char *s);
int is_special(char *command);
void print_env(char **env);

/*======== RUN COMMANDS ==========*/
int	run_command(char **av, char **envp, char *buff, infs_t *infs);
int shell_loop(char **av, int fd, infs_t *infs);
void free_func(char **strings);
void flush_infs(infs_t *infs);
int check_term(int fd);
int cmd_exec(char *cmd, infs_t *infs, char **av, char **envp);

#endif

