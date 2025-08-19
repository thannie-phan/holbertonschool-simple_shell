#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t len = 0;
	pid_t pid;
	int status;
	int interactive = isatty(1);


while (1)
{
        /* Display prompt only if interactive */
	if (interactive)
		printf("cisfun ");

        /* Read command from user */
	if (getline(&line, &len, stdin) == -1)
	{
		if (interactive)
		{
              /* actual input error */
            printf("\n");
            fprintf(sterr, "%s: read: input error\n" av[0]);
		    break; /*exit */
		}
	}
        /* Remove newline character */
	line[strcspn(line, "\n")] = '\0';

        /* Create child process */
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(line);
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
       /* Child process runs command (no arguments) */
		char *args[] = {line, NULL};
		if (execve(line, args, env) == -1)
		{
			perror("execve");
			free(line);
			exit(127);
		}
	}
	else
	{
            /* Parent waits for child to finish */
		waitpid(pid, &status, 0);
	}
}

return 0;
}
