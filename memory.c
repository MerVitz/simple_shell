#include "shell.h"

/**
 * safe_free - releases allocated memory and resets the pointer
 * @ptr: a double pointer referencing the memory to be released
 *
 * Return: 1 on successful release of memory, 0 if not executed.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr); // Deallocate memory block
		*ptr = NULL; // Set the pointer to NULL to avoid dangling references
		return (1); // Indicate successful deallocation
	}
	return (0); // Return 0 if no action was taken
}

