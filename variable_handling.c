#include "shell.h"

/**
 * replace_string - substitutes one string for another
 * @old: pointer to the string to be replaced
 * @new: string to replace with
 * This function replaces the contents of the pointer
 * to the old string with a new string
 * and deallocates the memory for the old string.
 * Return: 1 to indicate the operation was successful.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * is_chain - identifies command separators such as &&, ||, ;
 * @info: context containing shell information
 * @buf: command buffer to be parsed
 * @p: pointer to current position in the buffer
 *
 * Checks for the presence of a chain delimiter in the command
 * buffer and updates the parsing state accordingly.
 * Return: 1 if a delimiter is found, otherwise 0.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - assesses the need to proceed with command chaining
 * @info: context containing shell information and status
 * @buf: buffer containing the command chain
 * @p: pointer to the current buffer index
 * @i: index in the buffer to check from
 * @len: total length of the buffer
 *
 * This function determines whether to break out of a command chain
 * based on the result of the last command.
 * Return: It modifies the buffer to terminate the chain if necessary.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - seeks and replaces aliases in the tokenized command
 * @info: context containing shell information, including aliases
 *
 * Iterates over the aliases list and replaces any matching first
 * argument of the command
 * with its corresponding alias value.
 * Return: 1 if an alias was replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - substitutes variables within the command arguments
 * @info: context containing shell information, including variables
 *
 * Scans through the argument list, replacing any recognized
 * variables with their values.
 * Unrecognized variables are replaced with an empty string.
 * Return:0
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}


