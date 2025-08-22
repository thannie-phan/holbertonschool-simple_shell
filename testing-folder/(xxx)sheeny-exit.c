#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stddef.h>
#include <stdint.h>

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
        
        if (charsRead == -1)
		{
			free(input_line);
			return (NULL);
		}

    	if (charsRead > 0 && input_line[charsRead - 1] == '\n')
		    input_line[charsRead - 1] = '\0';
	
	return (input_line);
}

int count_words(char *str)
{
	int count;
	char *words;
	
	count = 0;
	
	words = strtok(str, " ");
	while (words != NULL)
	{
		count++;
		words = strtok(NULL, " ");
	}

	return (count);
}

char **split_string(char *str)
{
	char **words_array;
	char *word, *str_copy, *copy_to_count;
	int count, slot, free_count;
	
	slot = 0, free_count = 0;

	if (str == NULL)
		return (NULL);

	copy_to_count = strdup(str);
	if (copy_to_count == NULL)
		return (NULL);

	count = count_words(copy_to_count);
	free(copy_to_count);
	if (count == 0)
		return (NULL);
	words_array = malloc(sizeof(char *) * (count + 1));
	if (words_array == NULL)
		return (NULL);
	
	str_copy = strdup(str);
	if (str_copy == NULL)
	{
		free(words_array);
		return (NULL);
	}

	word = strtok(str_copy, " ");
	while (word != NULL)
	{
		words_array[slot] = strdup(word);
		if (words_array[slot] == NULL)
		{
			while (free_count < slot)
			{
				free(words_array[free_count]);
				free_count++;
			}
			free(words_array);
			free(str_copy);
			return (NULL);
		}
		slot++;
		word = strtok(NULL, " ");
	}

	words_array[slot] = NULL;
	free(str_copy);
	return (words_array);
}

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

void _printenv(void)
{
	extern char **environ;
	char **temp = environ;

	while (*temp != NULL)
	{
		printf("%s\n", *temp);
		temp++;
	}
}

char *find_command_in_path(char *command)
{
    char *path_env, *path_copy, *directory, *full_path;
    int cmd_length;

	if (strchr(command, '/') != NULL)
    {
        if (access(command, X_OK) == 0)
            return strdup(command);
        return NULL;
    }

    path_env = _getenv("PATH");
    if (path_env == NULL)
        return NULL;

    path_copy = strdup(path_env);
    if (path_copy == NULL)
        return NULL;

    cmd_length = strlen(command);
    directory = strtok(path_copy, ":");

    while (directory != NULL)
    {
        full_path = malloc(strlen(directory) + cmd_length + 2);
        if (full_path == NULL)
        {
            free(path_copy);
            return NULL;
        }

        sprintf(full_path, "%s/%s", directory, command);

        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return full_path;
        }

        free(full_path);
        directory = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

int *execute_command(char **args, int *exit_status)
{
	pid_t child_pid;
	int status;
	char *executable_path;
	extern char **environ;

	executable_path = find_command_in_path(args[0]);
	if (executable_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", progname, line_no, args[0]);
		free(executable_path);
		exit_status[1] = 127;
		return (exit_status);
	}
	child_pid = fork();
	
	if (child_pid == -1)
	{
		perror("fork");
		free(executable_path);
		exit_status[0] = 1; /* parent exit status is 1 */
		return (exit_status);
	}

	if (child_pid == 0)
	{
		if (execve(executable_path, args, environ) == -1) 
		{
			fprintf(stderr, "%s: %d: %s: not found\n", progname, line_no, args[0]);
			free(executable_path);
			exit_status[0] = 127; /* parent exit status is 127 */
			return (exit_status);
		}
	}
	else
	{
		wait(&status);
		free(executable_path);
	}
	if (WIFEXITED(status))
		exit_status[1] = WEXITSTATUS(status);
	return (exit_status);
}

int main(int argc, char **argv)
{
	char *command;
	char **args;
	int *exit_status;
	int exit_code;

	(void)argc;
	progname = argv[0];
	exit_status = malloc(sizeof(int) * 2);
	exit_status[0] = 0;
	exit_status[1] = 0;

	while (1)
	{
		command = read_input();
		if (command == NULL)
		{
			free(exit_status);
			exit(0);
		}

		args = split_string(command);

		if (args != NULL)
		{
			if (strcmp(args[0], "exit") == 0)
			{
				free_args(args);
				free(command);
				exit_code = exit_status[1];
				free(exit_status);
				exit(exit_code);
			}
			if (strcmp(args[0], "env") == 0)
			{
				_printenv();
				free_args(args);
				free(command);
				continue;
			}
			exit_status = execute_command(args, exit_status);
			free_args(args);
		}
		    
		free(command);
		if (exit_status[0] != 0)
		{
			exit_code = exit_status[0];
                        free(exit_status);
			exit(exit_code);
		}
		line_no++;
		}
		
		exit_code = exit_status[1];
		free(exit_status);
		return (exit_code);
}
