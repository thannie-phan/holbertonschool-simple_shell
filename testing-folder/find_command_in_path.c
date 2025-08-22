#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "simple_shell_header.h"
/**
 * find_command_in_path - search PATH for command
 * @command: input command to search
 * Return: found command otherwise NULL
 */
char *find_command_in_path(char *command)
{
	char *path_env, *path_copy, *directory, *full_path;
	int cmd_length;

	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}
	path_env = _getenv("PATH");
	if (path_env == NULL)
		return (NULL);

	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	cmd_length = strlen(command);
	directory = strtok(path_copy, ":");
	while (directory != NULL)
	{
		full_path = malloc(strlen(directory) + cmd_length + 2);
		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", directory, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
		return (full_path);
		}

		free(full_path);
		directory = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
