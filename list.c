#include "shell.h"

/**
 * printListStr - prints the str elements of a list_t linked list
 * @h: pointer to head
 *
 * Return: size of list
 */
size_t printListStr(const list_t *h)
{
	size_t index;

	index = 0;
	while (h != NULL)
	{
		myPuts(h->str ? h->str : "(nil)");
		myPuts("\n");
		h = h->next;
		index++;
	}
	return (index);
}
/**
 * free_list - frees nodes of a list_t linked list
 * @head: address of pointer to head
 *
 * Return: Nothing
 */
void free_list(list_t **head)
{
	list_t *lastnode;
	list_t	*newnode, *headnode;

	if (!head || !*head)
		return;
	headnode = *head;
	lastnode = headnode;
	while (lastnode != NULL)
	{
		newnode = lastnode->next;
		free(lastnode->str);
		free(lastnode);
		lastnode = newnode;
	}
	*head = NULL;
}
/**
 * list_t_len - determines length of list_t linked list
 * @h: pointer to head
 *
 * Return: size of list
 */
size_t list_t_len(const list_t *h)
{
	size_t index;

	index = 0;
	while (h != NULL)
	{
		h = h->next;
		index++;
	}
	return (index);
}
/**
 * list_elements - returns an array of strings of the list->str
 * @head: pointer to head
 *
 * Return: array of strings
 */
char **list_elements(list_t *head)
{
	list_t *node = head;
	size_t n;
	size_t m;
	char **elements;
	char *str;

	n = list_t_len(head);
	if (!head || !n)
		return (NULL);
	elements = malloc(sizeof(char *) * (n + 1));
	if (elements == NULL)
		return (NULL);
	for (n = 0; node; node = node->next, n++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (str == NULL)
		{
			m = 0;
			while (m < n)
			{
				free(elements[m]);
				m++;
			}
			free(elements);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		elements[n] = str;
	}
	elements[n] = NULL;
	return (elements);
}

/**
 * printList - prints the elements of a list_t linked list
 * @h: pointer to head
 *
 * Return: size of list
 */
size_t printList(const list_t *h)
{
	size_t index;

	index = 0;
	while (h != NULL)
	{
		myPuts(convert_number(h->num, 10, 0));
		myPutchar(':');
		myPutchar(' ');
		myPuts(h->str ? h->str : "(nil)");
		myPuts("\n");
		h = h->next;
		index++;
	}
	return (index);
}
