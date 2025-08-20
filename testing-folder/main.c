#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
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
	int count, notallspaces, status;

	(void)argc;
	progname = argv[0];

	while (1)
	{
		command = read_input();
		if (command == NULL)
		    exit(0);

		if (strlen(command) == 0)
		{
			free(command);
			line_no++;
			continue;
		}
		count = 0, notallspaces = 0;
		while (command[count] != '\0')
		{
			if (command[count] != ' ')
			{
				notallspaces = 1;
			}
			count++;
		}
		if (notallspaces == 0)
		{
			free(command);
			line_no++;
			continue;
		}
		args = split_string(command);
		if (args != NULL)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				free_args(args);
				free(command);
				exit(0);

			}
			status = execute_command(args);
			free_args(args);
		}
		free(command);
		if (status != 0)
			exit(status);

		line_no++;
		}
		return (0);
}
