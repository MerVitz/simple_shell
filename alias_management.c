#include "shell.h"

/**
 * _myhistory - outputs the history list with line numbers
 * @info: structure containing shell state, including the history list
 *
 * Iterates through the history list and prints each command
 * with its corresponding line number.
 * Return: 0 after printing the entire history list.
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - deletes an alias from the list of aliases
 * @info: structure containing shell state, including the alias list
 * @str: string that represents the alias to be removed
 *
 * Separates the alias name from its value and removes the alias
 * from the list if found.
 * Return: 0 on successful removal, 1 if the alias was not found
 * or if an error occurred.
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - creates a new alias or updates an existing one
 * @info: structure containing shell state, including the alias list
 * @str: string that represents the alias and its value
 *
 * Analyzes the given string and either creates a new alias
 * or updates an existing one.
 * Return: 0 on success, 1 on failure to set the alias.
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (set_alias(info, str));

	set_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_list(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}


/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}



