#include "shell.h"

/**
 * _strncpy - replicates a subset of a source
 * string to a destination
 * @dest: the target buffer for copying
 * @src: the original string from which to copy characters
 * @n: the count of characters to replicate
 *
 * This function will copy 'n' characters from 'src' to 'dest'.
 * If 'src' has fewer than 'n'
 * characters, the remainder of 'dest' will be padded with null bytes.
 * Return: a pointer to the destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - appends characters from one string
 * to another up to a limit
 * @dest: the string to be appended to
 * @src: the string to append from
 * @n: the maximum number of characters to transfer
 *
 * Concatenates up to 'n' characters from 'src' onto the end
 * of 'dest'. If 'src' is shorter
 * than 'n', the concatenation stops at the null-terminator.
 * The destination string is always
 * null-terminated.
 * Return: the concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * _strchr - locates the first instance of a character in a string
 * @s: the string within which to search for the character
 * @c: the target character to find
 *
 * Searches through a string to find the first appearance of
 * a specified character, 'c'.
 * If the character is found, a pointer to its location in the
 * string is returned. If the character
 * Return: NULL.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
