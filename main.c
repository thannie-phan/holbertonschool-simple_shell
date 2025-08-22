#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "simple_shell_header.h"

int line_no;
char *progname;
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
	int *exit_status;
	int exit_code;

	(void)argc;
	progname = argv[0];
	exit_status = malloc(sizeof(int) * 2);
	exit_status[0] = 0;
	exit_status[1] = 0;

	while (1)
	{
		command = read_input();
		if (command == NULL)
		{
			exit_code = exit_status[1];
			free(exit_status);
			exit(exit_code);
		}
		
		args = split_string(command);
		if (args != NULL)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				free_args(args);
				free(command);
				exit_code = exit_status[1];
				free(exit_status);
				exit(exit_code);
			}
			if (strcmp(args[0], "env") == 0)
			{
				_printenv();
				free_args(args);
				free(command);
				continue;
			}
			exit_status = execute_command(args, exit_status);
			free_args(args);
		}

		free(command);
		if (exit_status[0] != 0)
		{
			exit_code = exit_status[0];
                        free(exit_status);
			exit(exit_code);
		}
		line_no++;
	}
		
	return (exit_code);
}
