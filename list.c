#include "shell.h"

/**
 * clear_list - deallocates all nodes in a linked list
 * @head_ptr: reference to the head node pointer
 *
 * Iteratively traverses a linked list, releasing the memory
 * for each node's string
 * Return: node itself, and finally nullifies the head pointer.
 */
void clear_list(list_t **head_ptr)
{
	list_t *node, *next_node;

	if (head_ptr && *head_ptr)
	{
		node = *head_ptr;
		while (node)
		{
			next_node = node->next;
			free(node->str);
			free(node);
			node = next_node;
		}
		*head_ptr = NULL;
	}
}

/**
 * remove_node_by_index - eliminates the node at a specified
 * index from a linked list
 * @head: reference to the head node pointer
 * @index: the position of the node to remove
 *
 * Successively navigates to the node at the given index
 * and removes it from the list,
 * taking care to properly link the list's remaining nodes.
 * Return: 1 on success, 0 if it fails.
 */
int remove_node_by_index(list_t **head, unsigned int index)
{
	list_t *current, *temp_node = NULL;
	unsigned int i = 0;

	if (head && *head)
	{
		if (index == 0)
		{
			temp_node = *head;
			*head = (*head)->next;
			free(temp_node->str);
			free(temp_node);
			return (1);
		}
		current = *head;
		while (current)
		{
			if (i == index)
			{
				temp_node->next = current->next;
				free(current->str);
				free(current);
				return (1);
			}
			temp_node = current;
			current = current->next;
			i++;
		}
	}
	return (0);
}

/**
 * display_list_strings - prints the string elements of a
 * list_t linked list
 * @h: pointer to the initial node
 *
 * Traverses the linked list and prints the string of each node.
 * Return: the number
 * of nodes traversed.
 */
size_t display_list_strings(const list_t *h)
{
	size_t nodes = 0;

	while (h)
	{
		puts(h->str ? h->str : "(nil)");
		puts("\n");
		h = h->next;
		nodes++;
	}
	return (nodes);
}

/**
 * append_node_to_end - appends a new node at the end of a list_t list
 * @head: reference to the head node pointer
 * @str: string to include in the new node
 * @num: the index to assign to the new node
 *
 * Constructs a new node and appends it to the end of the list,
 * updating the last node's next
 * reference.
 * Return: the pointer to the new node, or NULL on failure.
 */
list_t *append_node_to_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *current;

	new_node = malloc(sizeof(list_t));
	if (new_node == NULL)
		return (NULL);
	memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	new_node->str = str ? strdup(str) : NULL;
	if (new_node->str == NULL && str)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	if (head)
	{
		if (*head)
		{
			current = *head;
			while (current->next)
				current = current->next;
			current->next = new_node;
		}
		else
			*head = new_node;
	}
	return (new_node);
}

/**
 * prepend_node - inserts a new node at the beginning of a list_t list
 * @head: reference to the pointer to the head node
 * @str: the string to store in the new node
 * @num: the index value for the new node
 *
 * Generates a new node and places it at the start of the list,
 * shifting the head of the list
 * to this newly created node.
 * Return: the new node or NULL if the allocation fails.
 */
list_t *prepend_node(list_t **head, const char *str, int num)
{
	list_t *new_node;

	new_node = malloc(sizeof(list_t));
	if (new_node == NULL)
		return (NULL);
	memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	new_node->str = str ? _strdup(str) : NULL;
	if (new_node->str == NULL && str)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = head ? *head : NULL;
	if (head)
		*head = new_node;
	return (new_node);
}
