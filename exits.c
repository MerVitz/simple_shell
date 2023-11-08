#include "shell.h"

/**
 * locate_char - searches for the first occurrence of a character in a string
 * @s: the string to be searched
 * @c: the character to find
 *
 * This function scans a string for a specific character and returns a pointer
 * to the first occurrence of this character in the string.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++);

	return (NULL);
}

/**
 * string_concatenate - merges a certain amount of characters from one string to another
 * @dest: the string to be appended to
 * @src: the string to append from
 * @n: the maximum number of characters to append
 *
 * Appends up to n characters from the source to the destination string. 
 * If the source is shorter than n, the remaining space in the destination will be null-padded.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *result = dest;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j] && j < n)
	{
		dest[i++] = src[j++];
	}
	if (j < n)
		dest[i] = '\0';

	return (result);
}

/**
 * string_copy_n - duplicates a specified number of characters from a string
 * @dest: the buffer to copy to
 * @src: the source string to copy from
 * @n: the number of characters to copy
 *
 * Copies up to n characters from one string to another. If the source string is shorter
 * than n, the remainder of the destination string is filled with null bytes.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *result = dest;

	i = 0;
	while (src[i] && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	for (j = i; j < n; j++)
		dest[j] = '\0';

	return (result);
}
