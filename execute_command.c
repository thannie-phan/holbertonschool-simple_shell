#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "simple_shell_header.h"

/**
 * execute_command - fork a child process and execute command
 * @args: pointer to array of arguments
 * @exit_status: array for parent and child exit status
 *
 * Return: updated exit status array containing parent and child exit
 * status
 */

int *execute_command(char **args, int *exit_status)
{
	pid_t child_pid;
	int status;
	char *executable_path;

	executable_path = find_command_in_path(args[0]);
	if (executable_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", progname, line_no, args[0]);
		free(executable_path);
		exit_status[1] = 127; /* set child exit status */
		return (exit_status);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(executable_path);
		exit_status[0] = 1; /* set parent exit status */
		return (exit_status);
	}
	if (child_pid == 0)
	{
		if (execve(executable_path, args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", progname, line_no, args[0]);
			free(executable_path);
			exit_status[0] = 127; /* set parent exit status */
			return (exit_status);
		}
	}
	else
	{
		wait(&status);
		free(executable_path);
	}
	if (WIFEXITED(status)) /* i.e. child process exited in execve */
		exit_status[1] = WEXITSTATUS(status);
	return (exit_status);
}
