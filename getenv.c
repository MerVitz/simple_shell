#include "shell.h"

/**
 * get_environ - Retrieves the current environment
 * variable array
 * @info: Structure containing shell state, including environment variables
 *
 * Returns the current environment as a string array. If the
 * environment has changed,
 * the array is updated before being returned. Always
 * Return: 0.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Deletes an environment variable
 * @info: Structure with shell information and the environment list
 * @var: Variable name to search for and delete
 *
 * Iterates over the environment list to find and remove
 * the variable 'var'.
 * Return: 1 if the variable was deleted, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Changes or adds an environment variable
 * @info: Pointer to the main shell info structure
 * @var: The environment variable to set or modify
 * @value: The value to assign to the environment variable
 *
 * Allocates a new buffer and constructs the environment
 * string as 'VAR=VALUE'.
 * If the variable already exists, it updates the value;
 * otherwise, it adds a new variable.
 * Return: 0 on success, 1 on memory allocation failure.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
