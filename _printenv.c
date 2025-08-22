#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "simple_shell_header.h"

/**
 * _printenv - prints the current environment variables
 */
void _printenv(void)
{
	extern char **environ;
	char **env_copy;

	env_copy = environ;
	while (*env_copy != NULL)
	{
		printf("%s\n", *env_copy);
		env_copy++;
	}
}
