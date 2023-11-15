#include "shell.h"

/**
 * bfree - releases allocated memory and resets the pointer
 * @ptr: a double pointer referencing the memory to be released
 *
 * Return: 1 on successful release of memory, 0 if not executed.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

