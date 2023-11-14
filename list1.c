#include "shell.h"

/**
 * retrieve_node_index - fetches the position of a node in a list
 * @head: pointer to the start of the list
 * @node: the specific node to find the index for
 *
 * This function traverses the list from the beginning to
 * locate the node in question,
 * Return: the zero-based index of its position within the list.
 */
ssize_t retrieve_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

/**
 * find_node_prefix - locates a node where the string
 * begins with a specified prefix
 * @node: starting node for the search
 * @prefix: leading characters to match in the node's string
 * @c: character that must follow the prefix for a successful match
 *
 * Searches through a linked list and
 * Return: the first node where the string matches the prefix
 * followed by the specified character, or NULL if no match is found.
 */
list_t *find_node_prefix(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * echo_list - outputs the contents of a linked list
 * @h: pointer to the start of the list
 *
 * Iterates over a linked list and prints each element's
 * index and string to standard output.
 * Return: the number of elements printed.
 */
size_t echo_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		puts(convert_number(h->num, 10, 0));
		putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_array - converts a linked list to an array of strings
 * @head: pointer to the start of the list
 *
 * Creates a new array of strings by duplicating the
 * strings stored in each element of the list.
 * Return: a pointer to the array or NULL if the allocation fails.
 */
char **list_to_array(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * count_list - calculates the total number of nodes in a linked list
 * @h: pointer to the first node of the list
 *
 * Tallies the number of nodes in a linked list from
 * the first node to the end.
 * Return: the count as a size_t value.
 */
size_t count_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}
