#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "simple_shell_header.h"

/**
 * count_words - function to count the number of words in the supplied
 * string
 * @str: pointer to the string to count
 *
 * Return: number of words in the string
 */
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
/**
 * mem_words_array - allocate memory for words array
 * @str: pointerto string
 *
 * Return: pointer array of words
 */
char **mem_words_array(char *str)
{
	char *copy_to_count;
	char **words_array;
	int count;

	copy_to_count = strdup(str);
	if (copy_to_count == NULL) /* if strdup failed */
	{
		return (NULL);
	}

	count = count_words(copy_to_count);
	free(copy_to_count);
	if (count == 0) /* i.e. only spaces in string */
	{
		return (NULL);
	}
	/* allocate memory for number of commands and null byte */
	words_array = malloc(sizeof(char *) * (count + 1));
		return (words_array);
}

/**
 * split_string - function to split a string into each word and store
 * the words in a pointer array
 * @str: pointer to string to split
 *
 * Return: pointer array of words
 */
char **split_string(char *str)
{
	char **words_array; /* array to store pointer to words */
	char *word, *str_copy;
	int slot, free_count;

	slot = 0;
	free_count = 0;

	if (str == NULL)
		return (NULL);
	words_array = mem_words_array(str);

	if (words_array == NULL)
		return (NULL);
	str_copy = strdup(str);
	if (str_copy == NULL)
	{
		free(words_array);
		return (NULL);
	}
	word = strtok(str_copy, " "); /* extract 1st word */
	while (word != NULL)
	{
		words_array[slot] = strdup(word);
		if (words_array[slot] == NULL) /* if dup fail, free memory */
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
		word = strtok(NULL, " "); /* get next word */
	}
	words_array[slot] = NULL; /* end with NULL after last word */
	free(str_copy); /* free copy after tokenisation	*/
	return (words_array);
}
