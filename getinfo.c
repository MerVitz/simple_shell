#include "shell.h"

/**
 * release_info_resources - deallocates memory of
 * info_t struct fields
 * @info: reference to the shell state structure
 * @all: flag to indicate if all or partial resources should be freed
 *
 * This function is responsible for freeing the memory allocated
 * to fields within the info_t structure.
 * Return: all or part of the resources based on the 'all' flag.
 */
void release_info_resources(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * establish_info - sets up the info_t struct with
 * command line arguments
 * @info: pointer to the shell state structure
 * @av: argument vector from main
 *
 * This function initializes the info_t structure with the
 * filename and processes any arguments
 * Return: present in the info->arg field by tokenizing them into
 * info->argv and performing variable and alias replacement.
 */
void establish_info(info_t *info, char **av)
{
	int i;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i];
				i++);
		info->argc = i;
		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * reset_info - resets the fields of info_t struct to default states
 * @info: reference to the shell state structure
 *
 * Resets the various fields within the info_t structure
 * in preparation for processing a new command.
 * Return: This function is typically called at the start of a
 * new command loop.
 */
void reset_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
