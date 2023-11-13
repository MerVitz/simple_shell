#include "shell.h"

/**
 * _atoi - converts string to integer, ignoring non-numeric leading characters
 * @s: the string that represents an integer
 *
 * Parses the string to extract an integer value.
 * Handles negative numbers by detecting a '-' sign.
 * The conversion continues until a non-digit character is encountered if
 * an initial digit has been identified.
 * Return: Zero if no number are in the string otherwise, converted number
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result = result * 10 + (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	output = sign == -1 ? -result : result;
	return (output);
}

/**
 * _isalpha - determines if a character is an alphabetic letter
 * @c: the character to be checked
 *
 * Return: 1 if the character is a letter, 0 otherwise.
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * is_delim - checks if a character is among a set of delimiters
 * @c: the character to check
 * @delim: the delimiter string
 *
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * interactive - assesses if the shell is running in interactive mode
 * @info: shell state information
 *
 * Determines if the shell is interacting with a user or running
 * from a script by checking the file descriptor.
 * Return: 1 for interactive mode, 0 for non-interactive.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
