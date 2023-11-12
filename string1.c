#include "shell.h"

/**
 * replicate_string - duplicates the content of one string to another location
 * @dest: target location where the string will be copied
 * @src: source string to be copied
 *
 * This function replicates the content of the source string
 * into the destination buffer,
 * ensuring the destination has a copy of the string.
 * Return: the destination pointer.
 */
char *replicate_string(char *dest, char *src)
{
	int i = 0;

	if (dest == src || !src)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * generate_duplicate - generates a new memory allocation 
 * containing the same string
 * @str: the original string to duplicate
 *
 * This function allocates new memory and copies the input string into it,
 * Return: a pointer to the newly allocated duplicate.
 */
char *generate_duplicate(const char *str)
{
	int length = 0;
	char *ret;

	if (!str)
		return (NULL);
	while (str[length])
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	_strcpy(ret, str);
	return (ret);
}

/**
 * echo_string - prints a given string to standard output
 * @str: the string to be echoed
 *
 * By invoking the character-wise output function, 
 * Return: writes an entire string to stdout.
 */
void echo_string(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i])
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * buffered_char_output - writes characters to stdout with
 * buffering capabilities
 * @c: character to be printed, or control character to manage the buffer
 *
 * This function manages a static buffer to collect characters 
 * and writes them to stdout
 * in a batch. It's designed to be efficient by reducing
 * Return: number of write calls.
 */
int buffered_char_output(char c)
{
	static int i = 0;
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
