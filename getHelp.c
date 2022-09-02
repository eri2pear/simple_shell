#include "main.h"

/**
 * get_help - function that gets help messages according builtin used
 * @dstruct: data structure
 * Return: Return 1 on success
 */
int get_help(data_shell *dstruct)
{

	if (dstruct->args[1] == 0)
		aux_help_general();
	else if (_strcmp(dstruct->args[1], "setenv") == 0)
		aux_help_setenv();
	else if (_strcmp(dstruct->args[1], "env") == 0)
		aux_help_env();
	else if (_strcmp(dstruct->args[1], "unsetenv") == 0)
		aux_help_unsetenv();
	else if (_strcmp(dstruct->args[1], "help") == 0)
		aux_help();
	else if (_strcmp(dstruct->args[1], "exit") == 0)
		aux_help_exit();
	else if (_strcmp(dstruct->args[1], "cd") == 0)
		aux_help_cd();
	else if (_strcmp(dstruct->args[1], "alias") == 0)
		aux_help_alias();
	else
		write(STDERR_FILENO, dstruct->args[0],
			  _strlen(dstruct->args[0]));

	dstruct->status = 0;
	return (1);
}
