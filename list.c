#include "shell.h"

/**
 * add_node - inserts a new node at the beginning of a list_t list
 * @head: reference to the pointer to the head node
 * @str: the string to store in the new node
 * @num: the index value for the new node
 *
 * Generates a new node and places it at the start of the list,
 * shifting the head of the list
 * to this newly created node.
 * Return: the new node or NULL if the allocation fails.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - appends a new node at the end of a list_t list
 * @head: reference to the head node pointer
 * @str: string to include in the new node
 * @num: the index to assign to the new node
 *
 * Constructs a new node and appends it to the end of the list,
 * updating the last node's next
 * reference.
 * Return: the pointer to the new node, or NULL on failure.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints the string elements of a
 * list_t linked list
 * @h: pointer to the initial node
 *
 * Traverses the linked list and prints the string of each node.
 * Return: the number
 * of nodes traversed.
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - eliminates the node at a specified
 * index from a linked list
 * @head: reference to the head node pointer
 * @index: the position of the node to remove
 *
 * Successively navigates to the node at the given index
 * and removes it from the list,
 * taking care to properly link the list's remaining nodes.
 * Return: 1 on success, 0 if it fails.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - deallocates all nodes in a linked list
 * @head_ptr: reference to the head node pointer
 *
 * Iteratively traverses a linked list, releasing the memory
 * for each node's string
 * Return: node itself, and finally nullifies the head pointer.
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
