#include "shell.h"

/**
 * capture_signal - intercepts the SIGINT signal to prevent shell exit
 * @sig_num: the signal number received, expected to be SIGINT
 *
 * Instead of terminating the shell, it flushes the output buffer and
 * prompts a new command line. This function is a custom signal handler.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

/**
 * read_from_source - reads input from a file descriptor into a buffer
 * @info: parameter struct containing the file descriptor
 * @buf: buffer to read into
 * @i: current position in buffer
 *
 * This function reads input into a buffer from a file descriptor
 * specified in info.
 * It returns the number of bytes read or -1 on error.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * acquire_line - retrieves a line of input from a file descriptor
 * @info: pointer to the shell info structure containing file 
 * descriptor for input
 * @ptr: address of pointer to buffer, to store the input line
 * @length: size of preallocated buffer if not NULL
 *
 * Reads input until a newline or EOF is encountered. It manages 
 * a static buffer to
 * keep track of the input state across multiple calls. 
 * Return: the length of the line read.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * process_input_chain - processes chained commands from input buffer
 * @info: pointer to the shell info structure
 * @buf: address of input buffer containing command chain
 * @len: address of length variable tracking the buffer size
 *
 * Manages the parsing and execution of chained commands read
 * into the input buffer.
 * Handles input retrieval, command separation, and history logging.
 * Returns the number of bytes processed.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			*len = r;
			info->cmd_buf = buf;
		}
	}
	return (r);
}

/**
 * fetch_input - retrieves and processes a single command or a chain of commands
 * @info: pointer to the shell info structure
 *
 * Coordinates the retrieval of input lines and manages command
 * chaining by checking for semicolons.
 * Handles command history and buffer management.
 * Returns the length of the command to be executed.
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}
