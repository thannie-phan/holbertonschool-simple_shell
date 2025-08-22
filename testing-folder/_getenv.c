#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/**
 * _getenv - get the environment
 * @name: name of environment to search
 * Return: the environment otherwise NULL if fail
 */
char *_getenv(const char *name)
{
	extern char **environ;

	size_t len = strlen(name);
	int pos = 0;

	while (environ[pos] != NULL)
	{
		if (strncmp(environ[pos], name, len) == 0 && *(environ[pos] + len) == '=')
		{
			return (environ[pos] + len + 1);
		}
		pos++;
	}
return (NULL);
}
