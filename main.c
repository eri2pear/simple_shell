#include "main.h"

/**
 * free_data - frees data structure
 *
 * @dstruct: data structure
 * Return: no return value
 */
void free_data(data_shell *dstruct)
{
	unsigned int i;

	for (i = 0; dstruct->_environ[i]; i++)
	{
		free(dstruct->_environ[i]);
	}

	free(dstruct->_environ);
	free(dstruct->pid);
}

/**
 * set_data - used to itialize data structure
 *
 * @dstruct: data structure
 * @av: argument vector
 * Return: no return
 */
void set_data(data_shell *dstruct, char **av)
{
	unsigned int i;

	dstruct->av = av;
	dstruct->input = NULL;
	dstruct->args = NULL;
	dstruct->status = 0;
	dstruct->counter = 1;

	for (i = 0; environ[i]; i++)

	dstruct->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)

	dstruct->_environ[i] = _strdup(environ[i]);
	dstruct->_environ[i] = NULL;
	dstruct->pid = aux_itoa(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell dstruct;
	(void)ac;

	signal(SIGINT, get_sigint);
	set_data(&dstruct, av);
	shell_loop(&dstruct);
	free_data(&dstruct);
	if (dstruct.status < 0)
		return (255);
	return (dstruct.status);
}
