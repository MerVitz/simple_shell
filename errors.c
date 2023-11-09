#include "shell.h"

/**
 * write_to_file_descriptor - writes a single character to a specified file descriptor
 * @c: the character to output
 * @fd: the file descriptor to which the character will be written
 *
 * Buffers the character and writes it to the specified file descriptor. The buffer is flushed when full or when commanded.
 * Returns 1 on success, or -1 if an error occurs and sets errno.
 */
int _putfd(char c, int fd)
{
	static int i = 0;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i); // Flush the buffer to the file descriptor.
		i = 0; // Reset the buffer index.
	}
	if (c != BUF_FLUSH)
		buf[i++] = c; // Store the character in the buffer.
	return (1);
}

/**
 * print_string_to_fd - outputs a string to a given file descriptor
 * @str: the string to print
 * @fd: the file descriptor to write to
 *
 * This function sends each character of a string to the _putfd function to write to the specified file descriptor.
 * Returns the total number of characters written.
 */
int _putsfd(char *str, int fd)
{
	int count = 0;

	while (str && *str)
	{
		count += _putfd(*str++, fd); // Write each character to the file descriptor.
	}
	return (count); // Return the number of characters written.
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
		write(2, buf, i); // Flush the buffer to stderr.
		i = 0; // Reset the buffer index.
	}
	if (c != BUF_FLUSH)
		buf[i++] = c; // Store the character in the buffer.
	return (1);
}

/**
 * print_error_string - outputs an error message to stderr
 * @str: the error message to print
 *
 * Iterates through the error message string, passing each character to the _eputchar function to write to stderr.
 */
void _eputs(char *str)
{
	while (str && *str)
	{
		_eputchar(*str++); // Write each character to stderr.
	}
}
