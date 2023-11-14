#include "shell.h"

/**
 * display_history - outputs the history list with line numbers
 * @info: structure containing shell state, including the history list
 *
 * Iterates through the history list and prints each command
 * with its corresponding line number.
 * Return: 0 after printing the entire history list.
 */
int display_history(info_t *info)
{
	count_list(info->history);
}

/**
 * remove_alias - deletes an alias from the list of aliases
 * @info: structure containing shell state, including the alias list
 * @str: string that represents the alias to be removed
 *
 * Separates the alias name from its value and removes the alias
 * from the list if found.
 * Return: 0 on successful removal, 1 if the alias was not found
 * or if an error occurred.
 */
int remove_alias(info_t *info, char *str)
{
	char *equal_sign_position;
	int result;

	equal_sign_position = strchr(str, '=');
	if (!equal_sign_position)
		return (1);

	*equal_sign_position = '\0';
	result = remove_node_at_index(&(info->alias),
		retrieve_node_index(info->alias, starts_with(info->alias, str, -1)));
	*equal_sign_position = '=';
	return (result);
}

/**
 * create_or_update_alias - creates a new alias or updates an existing one
 * @info: structure containing shell state, including the alias list
 * @str: string that represents the alias and its value
 *
 * Analyzes the given string and either creates a new alias
 * or updates an existing one.
 * Return: 0 on success, 1 on failure to set the alias.
 */
int create_or_update_alias(info_t *info, char *str)
{
	char *equal_sign_position;

	equal_sign_position = _strchr(str, '=');
	if (!equal_sign_position)
		return (1);

	if (!*(equal_sign_position + 1))
		return (output_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * output_alias - prints a formatted representation of an alias
 * @node: the list node containing the alias string
 *
 * Formats and prints an alias in the form 'name=value'.
 * If the node is NULL, returns 1.
 * Otherwise,
 * Return: 0 after printing the alias.
 */
int output_alias(list_t *node)
{
	char *equal_sign_position, *alias_name;

	if (node)
	{
		equal_sign_position = _strchr(node->str, '=');
		for (alias_name = node->str; alias_name <= equal_sign_position; alias_name++)
			_putchar(*alias_name);

		_putchar('\'');
		_puts(equal_sign_position + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manage_alias - handles alias creation, updating, and printing
 * @info: structure containing shell state, including the
 * alias list and argument vector
 *
 * Processes the alias-related commands, creating, updating,
 * or printing aliases based on the input arguments.
 * Return: 0 after processing the commands.
 */
int manage_alias(info_t *info)
{
	if (info->argc == 1)
	{
		for (list_t *node = info->alias; node; node = node->next)
			print_alias(node);
	}
	else
	{
		for (int i = 1; info->argv[i]; i++)
		{
			char *equal_sign_position = _strchr(info->argv[i], '=');

			if (equal_sign_position)
				set_alias(info, info->argv[i]);
			else
				print_alias(node_starts_with(info->alias, info->argv[i], '='));
		}
	}

	return (0);
}
