#include "shell.h"

/**
 * convert_string_to_int - converts string to integer, ignoring non-numeric leading characters
 * @s: the string that represents an integer
 *
 * Parses the string to extract an integer value. Handles negative numbers by detecting a '-' sign.
 * The conversion continues until a non-digit character is encountered if an initial digit has been identified.
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1; // Toggle the sign with each '-' found.

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1; // Mark that we've started parsing a number.
			result = result * 10 + (s[i] - '0'); // Build the integer result.
		}
		else if (flag == 1) // If we've already started a number, stop converting on non-digit.
			flag = 2;
	}

	output = sign == -1 ? -result : result; // Apply the sign to the result.
	return (output);
}

/**
 * check_if_alpha - determines if a character is an alphabetic letter
 * @c: the character to be checked
 *
 * Returns 1 if the character is a letter, 0 otherwise.
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1); // Check for both lowercase and uppercase alphabetic characters.
	else
		return (0);
}

/**
 * verify_delimiter - checks if a character is among a set of delimiters
 * @c: the character to check
 * @delim: the delimiter string
 *
 * Returns 1 if the character is a delimiter, 0 otherwise.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1); // Check against each character in the delimiter string.
	return (0);
}

/**
 * check_interactive_mode - assesses if the shell is running in interactive mode
 * @info: shell state information
 *
 * Determines if the shell is interacting with a user or running from a script by checking the file descriptor.
 * Returns 1 for interactive mode, 0 for non-interactive.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2); // Check if STDIN is connected to a terminal.
}
