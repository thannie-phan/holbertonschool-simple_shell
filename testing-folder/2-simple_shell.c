#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

/**
 * main - simple shell that can run commands with their full path,
 * without any arguments
 * @ac: argument count
 * @av: array of arguments
 * @env: array of environment variables
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	char *line;
	size_t len = 0;
	ssize_t read;
	pid_t child_pid;
	char *argv[] = {"", NULL};
	int status;
	int interactive_mode; /* 1 for interactive mode, 0 for non-interactive */
	int line_count = 1;
	interactive_mode = isatty(fileno(stdin));
	(void)ac;

	while (1) /* infinite loop */
	{
		/* print prompt in interactive mode */
		if (interactive_mode)
			printf("($) ");
		/* read a line in from stdin */
		read = getline(&line, &len, stdin);
		if (read == -1) /* unable to read line */
		{
			free(line);
			exit(EXIT_FAILURE);
		}
		else /* i.e. read was successful */
		{
			/* replace new line with null byte */
			if (line[read - 1] == '\n')
				line[read - 1] = '\0';
			argv[0] = line;
		}
		/* create child fork */
		child_pid = fork();
		if (child_pid == -1) /* error creating child */
		{
			free(line);
			perror("fork"); /* not sure if we need this? */
			exit(EXIT_FAILURE);
		}
		/* execute program if we are the child process */
		if (child_pid == 0)
		{
			if (execve(argv[0], argv, env) == -1)
			{
				/* could not find file */
				fprintf(stderr, "%s: %d: %s: not found\n",
						av[0], line_count, argv[0]);
				exit(127); /* error executing process */
			}
		}
		else /* wait for child to complete */
			wait(&status);
		line_count++;
	}
	free(line);
	return (0);
}
