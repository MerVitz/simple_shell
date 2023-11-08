#include "shell.h"

/**
 * eliminate_comments - nullifies comments within a command line
 * @buf: pointer to the command line string
 *
 * Scans the command line for a '#' character that signifies the start of a comment.
 * If found, the function replaces it with a null character to ignore the comment.
 */
void remove_comments(char *buf)
{
	for (int i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (i == 0 || buf[i - 1] == ' '))
		{
			buf[i] = '\0'; // Truncate the string at the start of a comment.
			break;
		}
}

/**
 * stringify_number - converts a long integer to a string representation
 * @num: the number to convert
 * @base: the numerical base for conversion
 * @flags: flags to determine the conversion process, like sign handling and letter case
 *
 * This function acts as a custom itoa, converting a given number to its string
 * equivalent in the specified base, with optional sign and letter case formatting.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *digits;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num; // Convert to unsigned if the number is negative.
		sign = '-'; // Prepare to add the negative sign.
	}

	digits = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49]; // Start at the end of the buffer.
	*ptr = '\0';

	do {
		*--ptr = digits[n % base]; // Convert current digit and step back in the buffer.
		n /= base; // Reduce the number.
	} while (n != 0);

	if (sign)
		*--ptr = sign; // Place the sign if the number was negative.

	return (ptr); // Return the pointer to the beginning of the number string.
}

/**
 * print_decimal - prints an integer to a specified file descriptor
 * @input: the integer to print
 * @fd: the file descriptor to print to
 *
 * Outputs an integer as a sequence of characters to the given file descriptor.
 * Handles negative numbers and prints the corresponding '-' sign.
 */
int print_d(int input, int fd)
{
	int (*printer)(char) = _putchar; // Function pointer for character output.
	int i, count = 0;
	unsigned int absolute, current;

	if (fd == STDERR_FILENO)
		printer = _eputchar; // Use the error output function for STDERR.

	if (input < 0)
	{
		absolute = -input; // Get the absolute value if negative.
		printer('-'); // Print the negative sign.
		count++; // Increment the print count.
	}
	else
		absolute = input;

	current = absolute;
	for (i = 1000000000; i > 1; i /= 10) // Loop through each decimal place.
	{
		if (absolute / i)
		{
			printer('0' + current / i); // Print the digit.
			count++; // Increment the print count.
		}
		current %= i; // Reduce to the remainder.
	}
	printer('0' + current); // Print the last digit.
	count++; // Increment the print count.

	return (count); // Return the total number of characters printed.
}

/**
 * print_error_msg - outputs an error message with context information
 * @info: the shell info structure containing program and argument details
 * @error_msg: the error message to print
 *
 * Constructs and prints a formatted error message to standard error, including the
 * shell program name, the line number, and the command that caused the error.
 */
void print_error(info_t *info, char *error_msg)
{
	_eputs(info->fname); // Print the shell program name.
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO); // Print the line number.
	_eputs(": ");
	_eputs(info->argv[0]); // Print the command.
	_eputs(": ");
	_eputs(error_msg); // Print the error message.
}

/**
 * parse_error_to_int - converts an error string to an integer
 * @s: the error string to convert
 *
 * Analyzes an error string to extract the numeric value it represents.
 * Returns the integer value of the string or -1 if conversion isn't possible.
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++; // Skip the plus sign; it's not needed for conversion.

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9') // Check if the character is a digit.
		{
			result = result * 10 + (s[i] - '0'); // Convert to int and add to result.
			if (result > INT_MAX)
				return (-1); // Return error if result exceeds max int value.
		}
		else
			return (-1); // Return error if non-digit character is found.
	}
	return (result); // Return the converted integer.
}
