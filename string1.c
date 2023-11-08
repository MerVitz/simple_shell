#include "shell.h"

/**
 * char_output - outputs a single character to standard output
 * @c: the character to be printed
 *
 * This function buffers characters and prints them in a batch to improve performance.
 * The buffer is flushed either when it's full or when a flush command is received.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * print_string - displays a string to standard output
 * @str: the string to be output
 *
 * This function sends a string to the _putchar function character by character.
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * string_clone - creates a copy of the given string
 * @str: the string to be cloned
 *
 * Allocates memory for a new copy of the string, and returns a pointer to it.
 * The memory must be freed by the caller.
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * string_copy - copies a string from source to destination
 * @dest: buffer to copy the string to
 * @src: the string to be copied
 *
 * After copying, the destination string is returned. The caller must ensure
 * that the destination buffer is large enough to hold the source string.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
