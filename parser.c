#include "shell.h"

/**
 * check_for_command - checks if the provided path points to an executable
 * @info: pointer to the structure holding the shell information
 * @path: the potential path of the executable file
 *
 * Return: 1 if the path is an executable, 0 if not
 */
int check_for_command(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * copy_characters - creates a copy of a subset of characters from a string
 * @pathstr: the string containing the PATH environment variable
 * @start: index to begin copying characters
 * @stop: index to end copying characters
 *
 * Return: pointer to the newly created string segment
 */
char *copy_characters(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * seek_cmd_path - searches for a command's path within the PATH variable
 * @info: the info struct holding shell context
 * @pathstr: string containing the PATH environment variable
 * @cmd: the command to locate
 *
 * Return: the full path to the command if it exists, or NULL if not found
 */
char *seek_cmd_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (find_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
