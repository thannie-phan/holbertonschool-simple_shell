#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int line_no = 1;
char *progname;

char *read_input(void)
{
	char *input_line;
	size_t size;
	ssize_t charsRead;
	int mode;
		
    input_line = NULL;
	size = 0;
	mode = isatty(0);
	
	if (mode == 1)
	{
	    printf("#cisfun$ ");
	    fflush(stdout);
	}
	   
    charsRead = getline(&input_line, &size, stdin);
        
        if (charsRead == -1) // if cannot read cause of wtv reason including end of file
		{
			free(input_line);
			return (NULL);
		}

    	if (charsRead > 0 && input_line[charsRead - 1] == '\n') // if the last character is a newline aka the end
		    input_line[charsRead - 1] = '\0'; // replace newline with NULL to properly end the string
	
return (input_line);
}

void execute_command(char *command)
{
	pid_t child_pid;
	int status;
	char *args[2];
	extern char **environ;

	args[0] = command;
	args[1] = NULL;

	child_pid = fork();
	if (child_pid == -1) // if cannot fork 
	{
		perror("fork");
		exit(1);
	}

	if (child_pid == 0)
	{
		if (execve(command, args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", progname, line_no, command); // if cannot execute because command not found, same template as given
			exit(127);
		}
	}
	else
	{
		wait(&status);
	}
}

int main(int argc, char **argv)
{
	char *command;
	(void)argc;
	progname = argv[0];

	while (1)
	{
		command = read_input();
		if (command == NULL)
		    exit(0); //still exit but 0 cause no error unlike the above exit(1)

		if (strlen(command) == 0)
		{
			free(command);
			line_no++;
			continue;
		}

		execute_command(command);
		free(command);
		line_no++;
	}

	return (0);
}
