#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
/**
 * execute_command - fork a child process and execute command
 * @args: pointer to array of arguments
 * Return: 0 if Success or exit status, otherwise error code if fail
 */

int execute_command(char **args)
{
	pid_t child_pid;
	int status;
	char *executable_path;

	extern char **environ;

	executable_path = find_command_in_path(args[0]);
	if (executable_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", progname, line_no, args[0]);
		return (127);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(executable_path);
		exit(1);
	}
	if (child_pid == 0)
	{
		if (execve(executable_path, args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", progname, line_no, args[0]);
			free(executable_path);
			exit(127);
		}
	}
	else
	{
		wait(&status);
		free(executable_path);
	}
	return (0);
}
