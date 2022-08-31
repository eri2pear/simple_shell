#include "main.h"

/**
 * bring_line - Function assigns the line var for get_line
 * @linePtr: Variable ptr that is been called to line
 * @buffer: Variable buffer stores the input ptr
 * @n: size of line
 * @j: size of buffer
 */
void bring_line(char **linePtr, size_t *n, char *buffer, size_t j)
{

	if (*linePtr == NULL)
	{
		if (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*linePtr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*linePtr = buffer;
	}
	else
	{
		_strcpy(*linePtr, buffer);
		free(buffer);
	}
}
/**
 * get_line - Function that Reads input from stream
 * @linePtr: Variable buffer stores the input
 * @n: Var n is the size of linePtr
 * @stream: Var stream is to read from line
 * Return: The number of bytes
 */
ssize_t get_line(char **linePtr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	bring_line(linePtr, n, buffer, input);
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}
