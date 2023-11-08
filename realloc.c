#include "shell.h"

/**
 * fill_memory - sets a block of memory to a specified value
 * @s: pointer to the start of the memory block
 * @b: the value to set in the memory block
 * @n: the number of bytes to set in the memory block
 * Return: pointer to the beginning of the memory block
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * array_free - deallocates a dynamically allocated array of strings
 * @pp: array of string pointers to be deallocated
 * 
 * This function iterates through an array of strings, freeing each one,
 * then finally frees the array itself.
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * resize_memory - changes the size of a previously allocated memory block
 * @ptr: reference to the memory block originally allocated with malloc
 * @old_size: the size of the allocated space for ptr
 * @new_size: the new size of the allocated space
 * 
 * Return: a pointer to the newly allocated memory, which is suitably 
 * aligned for any kind of variable and may be different from ptr.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	for (unsigned int i = 0; i < old_size; i++)
		p[i] = ((char *)ptr)[i];
	free(ptr);
	return (p);
}
