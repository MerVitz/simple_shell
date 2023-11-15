#include "shell.h"

/**
 * _eputs - outputs an error message to stderr
 * @str: the error message to print
 *
 * Iterates through the error message string, passing each
 * character to the _eputchar function to write to stderr.
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar- writes a single character to stderr
 * @c: the character to output
 *
 * Buffers the character and writes it to standard error.
 * The buffer is flushed when full or when commanded.
 * Return: 1 on success, or -1 on error with errno set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - writes a single character to a specified file
 * descriptor
 * @c: the character to output
 * @fd: the file descriptor to which the character will be written
 *
 * Buffers the character and writes it to the specified file descriptor.
 * The buffer is flushed when full or when commanded.
 * Return: 1 on success, or -1 if an error occurs and sets errno.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - outputs a string to a given file descriptor
 * @str: the string to print
 * @fd: the file descriptor to write to
 *
 * This function sends each character of a string to the
 * print_string_to_fd function to write to the specified file descriptor.
 * Return: the total number of characters written.
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
