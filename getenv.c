#include "shell.h"

/**
 * modify_environment - Changes or adds an environment variable
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
int modify_environment(info_t *info, char *var, char *value)
{
	char *buffer;
	list_t *current_node;
	char *delimiter_position;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);

	strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);

	current_node = info->env;
	while (current_node)
	{
		delimiter_position = starts_with(current_node->str, var);
		if (delimiter_position && *delimiter_position == '=')
		{
			free(current_node->str);
			current_node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		current_node = current_node->next;
	}

	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}

/**
 * discard_environment_variable - Deletes an environment variable
 * @info: Structure with shell information and the environment list
 * @var: Variable name to search for and delete
 *
 * Iterates over the environment list to find and remove
 * the variable 'var'.
 * Return: 1 if the variable was deleted, 0 otherwise.
 */
int discard_environment_variable(info_t *info, char *var)
{
	list_t *current_node = info->env;
	size_t index = 0;
	char *start_match;

	if (!current_node || !var)
		return (0);

	while (current_node)
	{
		start_match = starts_with(current_node->str, var);
		if (start_match && *start_match == '=')
		{
			info->env_changed = remove_node_by_index(&(info->env), index);
			index = 0;
			current_node = info->env;
			continue;
		}
		current_node = current_node->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * fetch_environment_snapshot - Retrieves the current environment
 * variable array
 * @info: Structure containing shell state, including environment variables
 *
 * Returns the current environment as a string array. If the
 * environment has changed,
 * the array is updated before being returned. Always
 * Return: 0.
 */
char **fetch_environment_snapshot(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		bfree(info->environ);
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}
