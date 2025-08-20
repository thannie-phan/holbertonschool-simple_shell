int main(int argc, char **argv)
{
	char *command;
	char **args;
	/* int count, notallspaces; */
	
	(void)argc;
	progname = argv[0];

	while (1)
	{
		command = read_input();
		if (command == NULL)
		    exit(0);

		/* this is all handled in split_string
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
		} */
		args = split_string(command);
		if (args != NULL)
		{
			execute_command(args);
			free_args(args);
		}
		free(command);
		line_no++;
		}
		return (0);
}
