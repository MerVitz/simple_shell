#include "shell.h"

/**
 * copy_partial_string - replicates a subset of a source 
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
char *copy_partial_string(char *dest, char *src, int n)
{
	int index = 0;
	while (src[index] && index < n - 1)
	{
		dest[index] = src[index];
		index++;
	}
	for (int padding = index; padding < n; padding++)
		dest[padding] = '\0';

	return dest;
}

/**
 * append_limited_chars - appends characters from one string 
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
char *append_limited_chars(char *dest, char *src, int n)
{
	int dest_len = 0, src_index = 0;
	while (dest[dest_len])
		dest_len++;
	while (src[src_index] && src_index < n)
		dest[dest_len++] = src[src_index++];
	if (src_index < n)
		dest[dest_len] = '\0';

	return dest;
}

/**
 * find_char - locates the first instance of a character in a string
 * @s: the string within which to search for the character
 * @c: the target character to find
 *
 * Searches through a string to find the first appearance of
 * a specified character, 'c'.
 * If the character is found, a pointer to its location in the
 * string is returned. If the character
 * Return: NULL.
 */
char *find_char(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return s;
		s++;
	}

	return NULL;
}
