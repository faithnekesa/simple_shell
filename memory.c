#include "shell.h"

/**
 * *_memset - sets the memory to a constant byte
 * @s: the pointer to the memory area
 * @size: the byte to fill *s with
 * @n: number of bytes
 *
 * Return: pointer to the memory area s
 */
char *_memset(char *s, char size, unsigned int n)
{
	unsigned int index;

	index = 0;
	while (index < n)
	{
		s[index] = size;
		index++;
	}
	return (s);
}
/**
 * p_free - frees a pointer
 * @p: address of the pointer to free
 *
 * Return: 1 on success, 0 otherwise
 */
int p_free(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
/**
 * s_free - frees a string of strings
 * @p: pointer to the  string
 *
 * Return: Nothing.
 */
void s_free(char **p)
{
	char **str = p;

	if (!p)
	{
		return;
	}
	while (*p != NULL)
	{
		free(*p++);
	}
	free(str);
}
/**
 * *_realloc - reallocates memory
 * @p: pointer to previous malloc'ated memory
 * @size1: number of bytes of malloc'ated memory
 * @size2: number bytes reallocated memory
 *
 * Return: pointer to malloc'ated memory
 */
void *_realloc(void *p, unsigned int size1, unsigned int size2)
{
	char *str;

	if (!p)
	{
		return (malloc(size2));
	}
	if (!size2)
	{
		return (free(p), NULL);
	}
	if (size2 == size1)
	{
		return (p);
	}
	str = malloc(size2);
	if (!str)
	{
		return (NULL);
	}
	size1 = size1 < size2 ? size1 : size2;
	while (size1--)
	{
		str[size1] = ((char *)p)[size1];
	}
	free(p);
	return (str);
}
