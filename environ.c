#include "shell.h"

/**
 * construct_env_list - creates a linked list from the environment variables
 * @info: shell state information, including the head of the env list
 *
 * Loops over the system environment variables
 * and appends each one to a new linked list.
 * The head of the list is stored in the info structure.
 * Return: 0.
 */
int construct_env_list(info_t *info)
{
	list_t *node = NULL;

	for (size_t i = 0; environ[i]; i++)

	{
		add_node_end(&node, environ[i], 0);
	}
	info->env = node;
	return (0);
}

/**
 * retrieve_env_value - obtains the value of an environment variable
 * @info: shell state information, used for accessing the env list
 * @name: the name of the environment variable to find
 *
 * Traverses the env linked list to find the variable
 * 'name' and returns its value.
 * Return: NULL if the variable is not found.
 */
char *retrieve_env_value(info_t *info, const char *name)
{
	for (list_t *node = info->env; node; node = node->next)
	{
		char *match = starts_with(node->str, name);
			return (match);
	}
	return (NULL);
}

/**
 * environment_variable_set - sets or updates an environment variable
 * @info: shell state information including the env list and argument count
 *
 * Checks for the correct number of arguments and then sets or
 * updates the specified environment variable.
 * Return:  on incorrect arguments or if the _setenv
 * function fails, otherwise 0.
 */
int environment_variable_set(info_t *info)
{
	if (info->argc != 3)
	{
		puts("Incorrect number of arguments\n");
		return (1);
	}
	return (setenv(info, info->argv[1], info->argv[2]) ? 0 : 1);
}

/**
 * environment_variable_unset - removes environment variables
 * @info: shell state information including the env list and argument count
 *
 * Removes the specified environment variables from the env list.
 * If no variables are specified,
 * an error message is printed.
 * Return: 0 after attempting to unset the variables.
 */
int environment_variable_unset(info_t *info)
{
	if (info->argc < 2)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (int i = 1; i < info->argc; i++)
	{
		unsetenv(info, info->argv[i]);
	}
	return (0);
}

/**
 * display_environment - prints the current environment to stdout
 * @info: shell state information including the env list
 *
 * Outputs the entire environment list to stdout, using the
 * print_list_str function.
 * Return: 0 always.
 */
int display_environment(info_t *info)
{
	print_list_str(info->env);
	return (0);
}
