/*
 * execute_command - fork execve and wait execution
 * @args: command arguments
 * Return: Success
 */

  
void execute_command(char **args)
{
  	pid_t child_pid;
  	int status;
  	extern char **environ;

  	child_pid = fork();
  	if (child_pid == -1)
  	{
  		perror("fork");
  		exit(1);
  	}

  	if (child_pid == 0)
  	{
  		if (execve(args[0], args, environ) == -1)
  		{
  			fprintf(stderr, "%s: %d: %s: not found\n", progname, line_no, args[0]);
  			exit(127);
      }
  	}
  	else
  	{
  		wait(&status);
  	}
}
