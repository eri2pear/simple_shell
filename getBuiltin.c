#include "main.h"

/**
 * get_builtin - builtin that runs the command in the arg
 * @cmnd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmnd))(data_shell *)
{
	builtin_t builtin[] = {
		{"env", _env},
		{"exit", exit_shell},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", cd_shell},
		{"help", get_help},
		{NULL, NULL}};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmnd) == 0)
			break;
	}

	return (builtin[i].f);
}
