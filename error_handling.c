#include "shell.h"

/**
 * _erratoi - converts an error string to an integer
 * @s: the error string to convert
 *
 * Analyzes an error string to extract the numeric value it represents.
 * Return: the integer value of the string or -1 if conversion isn't possible.
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - outputs an error message with context information
 * @info: the shell info structure containing program and argument details
 * @estr: the error message to print
 *
 * Constructs and prints a formatted error message to standard error
 * , including the
 * shell program name, the line number, and the command that caused the error.
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - prints an integer to a specified file descriptor
 * @input: the integer to print
 * @fd: the file descriptor to print to
 *
 * Outputs an integer as a sequence of characters to the given file descriptor.
 * Return: Handles negative numbers and prints the corresponding '-' sign.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converts a long integer to a string representation
 * @num: the number to convert
 * @base: the numerical base for conversion
 * @flags: flags to determine the conversion process, like sign
 * handling and letter case
 *
 * Return: a given number to its string equivalent in the specified base,
 * with optional sign and letter case formatting.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - nullifies comments within a command line
 * @buf: pointer to the command line string
 *
 * Scans the command line for a '#' character that signifies the start of
 * a comment.
 * If found, the function replaces it with a null
 * character to ignore the comment.
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
