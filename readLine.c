#include "main.h"

/**
 * read_line - Function to read the input string.
 *
 * @inteof: Var to return value of getline function
 * Return: input string
 */
char *read_line(int *inteof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*inteof = getline(&input, &bufsize, stdin);

	return (input);
}
