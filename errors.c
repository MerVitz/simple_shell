#include "shell.h"

/**
 * write_to_file_descriptor - writes a single character to a specified file descriptor
 * @c: the character to output
 * @fd: the file descriptor to which the character will be written
 *
 * Buffers the character and writes it to the specified file descriptor. The buffer is flushed when full or when commanded.
 * Returns 1 on success, or -1 if an error occurs and sets errno.
 */
int write_to_file_descriptor(char c, int fd)
{
	static int i = 0;
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
 * print_string_to_fd - outputs a string to a given file descriptor
 * @str: the string to print
 * @fd: the file descriptor to write to
 *
 * This function sends each character of a string to the 
 * print_string_to_fd function to write to the specified file descriptor.
 * Returns the total number of characters written.
 */
int print_string_to_fd(char *str, int fd)
{
	int count = 0;

	while (str && *str)
	{
		count += print_string_to_fd(*str++, fd); 
	}
	return (count);
}

/**
 * print_error_character - writes a single character to stderr
 * @c: the character to output
 *
 * Buffers the character and writes it to standard error. The buffer is flushed when full or when commanded.
 * Returns 1 on success, or -1 on error with errno set appropriately.
 */
int _eputchar(char c)
{
	static int i = 0;
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
 * print_error_string - outputs an error message to stderr
 * @str: the error message to print
 *
 * Iterates through the error message string, passing each character to the _eputchar function to write to stderr.
 */
void print_error_string(char *str)
{
	while (str && *str)
	{
		_eputchar(*str++);
	}
}
