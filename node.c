#include "shell.h"

/**
 * *add_node - adds new node at the beginning of list_t
 * @head: pointer to the head of list_t
 * @str: string to be copied
 * @num: index of used history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *newnode;

	if (head == NULL)
	{
		return (NULL);
	}
	newnode = malloc(sizeof(list_t));
	if (newnode == NULL)
	{
		return (NULL);
	}
	_memset((void *)newnode, 0, sizeof(list_t));
	newnode->num = num;
	if (str)
	{
		newnode->str = _strdup(str);
		if (newnode->str == NULL)
		{
			free(newnode);
			return (NULL);
		}
	}
	newnode->next = *head;
	*head = newnode;
	return (newnode);
}
/**
 * *add_node_end - adds a new node at the end of a list_t list
 * @head: pointer to the head of the list_t
 * @str: string to be duplicated
 * @num: index of used history
 *
 * Return: size of the list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *newnode;
	list_t *lastnode;

	if (head == NULL)
		return (NULL);
	newnode = *head;
	lastnode = malloc(sizeof(list_t));
	if (!newnode)
		return (NULL);
	_memset((void *)newnode, 0, sizeof(list_t));
	newnode->num = num;
	if (str)
	{
		newnode->str = _strdup(str);
		if (!newnode->str)
		{
			free(newnode);
			return (NULL);
		}
	}
	if (lastnode)
	{
		while (lastnode->next != NULL)
			lastnode = lastnode->next;
		lastnode->next = newnode;
	}
	else
		*head = newnode;
	return (newnode);
}
/**
 * delete_node - deletes node at given index
 * @head: address of pointer to head
 * @index: index of node to be deleted
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node(list_t **head, unsigned int index)
{
	list_t *newnode;
	list_t *lastnode;
	unsigned int n;

	n = 0;
	if (!head || !*head)
		return (0);

	if (!index)
	{
		newnode = *head;
		*head = (*head)->next;
		free(newnode->str);
		free(newnode);
		return (1);
	}
	newnode = *head;
	while (newnode != NULL)
	{
		if (n == index)
		{
			lastnode->next = newnode->next;
			free(newnode->str);
			free(newnode);
			return (1);
		}
		n++;
		lastnode = newnode;
		newnode = newnode->next;
	}
	return (0);
}
/**
 * node_prefix - returns node whose string starts with prefix
 * @node: pointer to head
 * @prefix: string to be treated
 * @c: character after prefix
 *
 * Return: match node,NULL otherwise
 */
list_t *node_prefix(list_t *node, char *prefix, char c)
{
	char *currentnode = NULL;

	while (node != NULL)
	{
		currentnode = begin_with(node->str, prefix);
		if (currentnode && ((c == -1) || (*currentnode == c)))
		{
			return (node);
		}
		node = node->next;
	}
	return (NULL);
}
/**
 * node_index - gets the index of a node
 * @head: pointer to head
 * @node: pointer to current node
 *
 * Return: index of node, -1 otherwise
 */
ssize_t node_index(list_t *head, list_t *node)
{
	size_t index;

	index = 0;
	while (head != NULL)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
