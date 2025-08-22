#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "simple_shell_header.h"

char *progname;
int line_no = 1;
/**
 * main - entry point for the shell
 * @argc: argument count
 * @argv: arguments
 * Return: 0 if Success or exit status, otherwise error code if fail
 */
int main(int argc, char **argv)
{
	char *command;
	char **args;
	int exit_status[2] = {0, 0};
	(void)argc;
	progname = argv[0];
	while (1)
	{
		command = read_input();
		if (command == NULL)
			exit(exit_status[1]);
		args = split_string(command);
		if (args != NULL)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				free_args(args);
				free(command);
				exit(exit_status[1]);
			}
			if (strcmp(args[0], "env") == 0)
			{
				_printenv();
				free_args(args);
				free(command);
				continue;
			}
			memcpy(exit_status, execute_command(args, exit_status),
					sizeof(exit_status));
			free_args(args);
		}
		free(command);
		if (exit_status[0] != 0)
			exit(exit_status[0]);
		line_no++;
	}
	return (exit_status[0]);
}
