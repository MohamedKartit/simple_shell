#ifndef _SHELL_H_
#define _SHELL_H_
/*========== LIBRARIES ==========*/

#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

extern char *environ;

typedef struct list_s {
    char *pro;
    char *args;
    char *pathname;
} list_t;

/*========== PRINTING ==========*/
int _putchar(char c);
int _puts(char *str);
int shell_loop(char **av, int fd);

#endif

