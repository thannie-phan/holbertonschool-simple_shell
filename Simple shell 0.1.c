#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stddef.h>

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

int execute_command(char **args)
{
	pid_t child_pid;
	int status;
	char *executable_path;
	
	extern char **environ;
	
	executable_path = find_command_in_path(args[0]);
	if (executable_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", progname, line_no, args[0]);
		return (127);
	}
	
	child_pid = fork();
	
	if (child_pid == -1)
	{
		perror("fork");
		free(executable_path);
		exit(1);
	}

	if (child_pid == 0)
	{
		if (execve(executable_path, args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", progname, line_no, args[0]);
			free(executable_path);
			exit(127);
		}
	}
	else
	{
		wait(&status);
		free(executable_path);

		if (WIFEXITED(status))
		{
		return (WEXITSTATUS(status));
		}
	}
	
		return (1);
}

int main(int argc, char **argv)
{
	char *command;
	char **args;
	int count, notallspaces, status, prev_fail;

	prev_fail = 0;

    (void)argc;
    progname = argv[0];

    while (1)
    {
        command = read_input();
        if (command == NULL)
            exit(0);

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
                notallspaces = 1;
            count++;
        }
        if (notallspaces == 0)
        {
            free(command);
            line_no++;
            continue;
        }

        args = split_string(command);

        if (args != NULL)
        {
            if (strcmp(args[0], "exit") == 0)
            {
                free_args(args);
                free(command);

                if (prev_fail != 0)
				{
					exit(2);
				}
                else
				{ 
					exit(0);
				}
            }

            status = execute_command(args);

            if (status != 0)
            {
                prev_fail = 1;
            }
            else
            {
                prev_fail = 0;
            }

            free_args(args);
        }

        free(command);
        line_no++;
    }
    return (0);
}
