#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/**
 * read_input - read line from stdin, handle errors, and remove newline
 *
 * Return: processed line from input
 */
char *read_input(void)
{
	char *input_line;
	size_t size;
	ssize_t charsRead;
	int interactive_mode; /* 1 if interactive mode, 0 if non-interactive */

	input_line = NULL;
	size = 0;
	mode = isatty(0);

	if (interactive_mode == 1)
	{
		printf("#cisfun$ ");
		fflush(stdout);
	}
	charsRead = getline(&input_line, &size, stdin);

	if (charsRead == -1) /* read failed */
	{
		free(input_line);
		return (NULL);
	}
	/* if the last character is a newline */
	if (charsRead > 0 && input_line[charsRead - 1] == '\n')
		input_line[charsRead - 1] = '\0'; /* replace with NULL byte */

return (input_line);
}
