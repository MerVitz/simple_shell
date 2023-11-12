#include "shell.h"

/**
 * update_history_numbers - recalculates the index 
 * numbers of each history entry
 * @info: structure containing shell state, including history list
 *
 * Iterates over the history list, assigning a 
 * new sequence number to each entry
 * based on its position. 
 * Return:  the total count of history entries.
 */
int update_history_numbers(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	info->histcount = i;
	return i;
}

/**
 * populate_history - constructs the history list from a buffer
 * @info: pointer to the shell state structure containing the history list
 * @buf: string buffer representing one history entry
 * @linecount: the line number to assign to the history entry
 *
 * Adds a new entry to the end of the history list using the provided buffer.
 * The linecount is assigned as the entry's index number. Always 
 * Return:  0.
 */
int populate_history(info_t *info, char *buf, int linecount)
{
	list_t *node = info->history;

	if (node)
	{
		while (node->next)
			node = node->next;
		add_node_end(&node, buf, linecount);
	}
	else
	{
		info->history = add_node_end(&node, buf, linecount);
	}

	return (0);
}

/**
 * fetch_history - reads history entries from a file
 * @info: pointer to the shell state structure containing the history list
 *
 * Opens the history file and reads its contents into the history list.
 * Each line is added as a separate entry. 
 * Return: the total number of history entries.
 */
int fetch_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1 || fstat(fd, &st) || (fsize = st.st_size) < 2)
		return (fd != -1 ? close(fd), 0 : 0);

	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	close(fd);
	if (rdlen <= 0)
		return (free(buf), 0);

	buf[fsize] = '\0';
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);

	renumber_history(info);
	return (info->histcount);
}

/**
 * save_history - writes the history list to a file
 * @info: pointer to the shell state structure containing the history list
 *
 * Writes each history entry to a file, creating or truncating it as necessary.
 * Return: 1 on success, or -1 if the file could not be written.
 */
int save_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = info->history;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);

	for (; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * locate_history_file - finds or creates the file used to store command history
 * @info: pointer to the shell state structure
 * containing environment variables
 *
 * Checks the HOME environment variable to determine the
 * directory for the history file,
 * then constructs the full path to the history file. 
 * Return: the path as a string.
 */
char *locate_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);

	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);

	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}
