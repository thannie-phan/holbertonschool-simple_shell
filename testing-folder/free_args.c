#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
/**
 * free_args - free allocated memory for arguments
 * @args: arguments to free
 * Return: Success
 */
void free_args(char **args)
{
	int count;

	if (args == NULL)
		return;

	count = 0;
	while (args[count] != NULL)
	{
		free(args[count]);
		count++;
	}
	free(args);
}
