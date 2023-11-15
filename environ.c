#include "shell.h"

/**
 * _getenv - obtains the value of an environment variable
 * @info: shell state information, used for accessing the env list
 * @name: the name of the environment variable to find
 *
 * Traverses the env linked list to find the variable
 * 'name' and returns its value.
 * Return: NULL if the variable is not found.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * populate_env_list - creates a linked list from the environment variables
 * @info: shell state information, including the head of the env list
 *
 * Loops over the system environment variables
 * and appends each one to a new linked list.
 * The head of the list is stored in the info structure.
 * Return: 0.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 * _mysetenv - removes environment variables
 * @info: shell state information including the env list and argument count
 *
 * Removes the specified environment variables from the env list.
 * If no variables are specified,
 * an error message is printed.
 * Return: 1 after attempting to unset the variables.
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myenv - prints the current environment to stdout
 * @info: shell state information including the env list
 *
 * Outputs the entire environment list to stdout, using the
 * print_list_str function.
 * Return: 0 always.
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _myunsetenv - sets or updates an environment variable
 * @info: shell state information including the env list and argument count
 *
 * Checks for the correct number of arguments and then sets or
 * updates the specified environment variable.
 * Return:  on incorrect arguments or if the _setenv
 * function fails, otherwise 0.
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}
