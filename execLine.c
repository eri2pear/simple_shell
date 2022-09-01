#include "main.h"

/**
 * exec_line - finds builtins and commands 
 *
 * @dstruct: data relevant (args)
 * Return: return 1 if success.
 */
int exec_line(data_shell *dstruct)
{
	int (*builtin)(data_shell * dstruct);

	if (dstruct->args[0] == NULL)
		return (1);

	builtin = get_builtin(dstruct->args[0]);

	if (builtin != NULL)
		return (builtin(dstruct));

	return (cmd_exec(dstruct));
}