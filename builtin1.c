#include "shell.h"

/**
 * display_history - outputs the history list with line numbers
 * @info: structure containing shell state, including the history list
 *
 * Iterates through the history list and prints each command with its corresponding line number.
 * Returns 0 after printing the entire history list.
 */
int _myhistory(info_t *info)
{
	print_list(info->history); // Calls print_list to display the history entries.
	return (0);
}

/**
 * remove_alias - deletes an alias from the list of aliases
 * @info: structure containing shell state, including the alias list
 * @str: string that represents the alias to be removed
 *
 * Separates the alias name from its value and removes the alias from the list if found.
 * Returns 0 on successful removal, 1 if the alias was not found or if an error occurred.
 */
int unset_alias(info_t *info, char *str)
{
	char *equal_sign_position;
	int result;

	equal_sign_position = _strchr(str, '=');
	if (!equal_sign_position)
		return (1); // If there's no '=' character, it's not a valid alias, return error.

	*equal_sign_position = '\0'; // Temporarily terminate the string at the '=' character to isolate the alias name.
	result = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*equal_sign_position = '='; // Restore the '=' character after operation.
	return (result); // Return the result of the deletion operation.
}

/**
 * create_or_update_alias - creates a new alias or updates an existing one
 * @info: structure containing shell state, including the alias list
 * @str: string that represents the alias and its value
 *
 * Analyzes the given string and either creates a new alias or updates an existing one.
 * Returns 0 on success, 1 on failure to set the alias.
 */
int set_alias(info_t *info, char *str)
{
	char *equal_sign_position;

	equal_sign_position = _strchr(str, '=');
	if (!equal_sign_position)
		return (1); // If '=' is not found, return error.

	if (!*(equal_sign_position + 1))
		return (unset_alias(info, str)); // If there's no value after '=', it's an unset operation.

	unset_alias(info, str); // Remove any existing alias with the same name.
	return (add_node_end(&(info->alias), str, 0) == NULL); // Attempt to add the new alias and return the result.
}

/**
 * output_alias - prints a formatted representation of an alias
 * @node: the list node containing the alias string
 *
 * Formats and prints an alias in the form 'name=value'. If the node is NULL, returns 1.
 * Otherwise, it returns 0 after printing the alias.
 */
int print_alias(list_t *node)
{
	char *equal_sign_position, *alias_name;

	if (node)
	{
		equal_sign_position = _strchr(node->str, '=');
		for (alias_name = node->str; alias_name <= equal_sign_position; alias_name++)
			_putchar(*alias_name); // Print the alias name.

		_putchar('\'');
		_puts(equal_sign_position + 1); // Print the alias value.
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manage_alias - handles alias creation, updating, and printing
 * @info: structure containing shell state, including the alias list and argument vector
 *
 * Processes the alias-related commands, creating, updating, or printing aliases based on the input arguments.
 * Returns 0 after processing the commands.
 */
int _myalias(info_t *info)
{
	if (info->argc == 1) // If there are no additional arguments, print all aliases.
	{
		for (list_t *node = info->alias; node; node = node->next)
			print_alias(node); // Call print_alias for each node in the alias list.
	}
	else
	{
		for (int i = 1; info->argv[i]; i++) // For each argument provided to alias...
		{
			char *equal_sign_position = _strchr(info->argv[i], '=');
			if (equal_sign_position)
				set_alias(info, info->argv[i]); // If there's an '=', attempt to set the alias.
			else
				print_alias(node_starts_with(info->alias, info->argv[i], '=')); // Otherwise, print the specified alias.
		}
	}

	return (0);
}
