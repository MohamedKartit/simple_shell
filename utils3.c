#include "shell.h"

/**
 * check_command - checks if the command exist
 * @cmd: the command
 * @paths: the paths to check in
 * Return: returns the full path or NULL
 */
char	*check_command(char *cmd, char **paths)
{
	char	*path_part;
	char	*command;

	command = NULL;
	path_part = NULL;
	if (!paths || !cmd)
		return (NULL);
	while (*paths)
	{
		path_part = _strjoin(*paths, "/");
		command = _strjoin(path_part, cmd);
		free(path_part);
		if (access(command, X_OK | F_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

/**
 * get_path - it gets the paths form PATH in the env
 * @envp: the environ
 * Return: returns the diffrent paths
 */
char	**get_path(char **envp)
{
	int		x;
	char	**cmd_paths;

	cmd_paths = NULL;
	x = 0;
	while (envp[x] && _strncmp("PATH=", envp[x], 5))
		x++;
	if (envp[x])
		cmd_paths = _strtok(envp[x] + 5, ':');
	return (cmd_paths);
}

/**
 * run_command - runs the command
 * @av: the argv
 * @envp: the environ
 * @infs: the struct that has infos about the command
 * Return: returns the exit status
 */
int run_command(char **av, char **envp, infs_t *infs)
{
	infs->cmd_args = _strtok(infs->buff, ' ');
	if (infs->cmd_args == NULL || infs->cmd_args[0] == NULL)
	{
		free_func(infs->cmd_args);
		free(infs->buff);
		return (0);
	}
	if (infs->isBuiltin == 1)
		return (exit_func(infs, av));
	else if (infs->isBuiltin == 2)
	{
		print_env(envp);
		flush_infs(infs);
		return (0);
	}
	infs->paths = get_path(envp);
	infs->cmd = check_command(infs->cmd_args[0], infs->paths);
	if (infs->cmd)
	{
		return (cmd_exec(infs->cmd, infs, envp));
	}
	else
	{
		if ((access(infs->cmd_args[0], F_OK) == 0) &&
				(infs->paths || infs->cmd_args[0][0] == '/'))
		{
			return (cmd_exec(infs->cmd_args[0], infs, envp));
		}
		else
		{
			error_printer(infs, av, ": not found\n");
			flush_infs(infs);
			return (127);
		}
	}
	return (0);
}

/**
 * cmd_exec - here where the command gets executed
 * @cmd: the command to be executed
 * @infs: the struct
 * @envp: the environ
 * Return: the exit status
 */
int cmd_exec(char *cmd, infs_t *infs, char **envp)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (child_pid == 0)
	{
		if (execve(cmd, infs->cmd_args, envp) == -1)
		{
			flush_infs(infs);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		flush_infs(infs);
		wait(&(infs->status));
		if (WIFEXITED(infs->status))
			infs->status = WEXITSTATUS(infs->status);
	}
	return (infs->status);
}
