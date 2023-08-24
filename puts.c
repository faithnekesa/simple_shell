#include "shell.h"

/**
 * *_strdup - duplicates a string
 * @str: the string to be duplicated
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int n;
	char *dupstr;

	n = 0;
	if (str == NULL)
	{
		return (NULL);
	}
	while (*str++)
	{
		n++;
	}
	dupstr = malloc(sizeof(char) * (n + 1));
	if (!dupstr)
	{
		return (NULL);
	}
	for (n++; n--;)
		dupstr[n] = *--str;
	return (dupstr);
}
/**
 * clearComments - replaces first instance of '#' with '\0'
 * @buf: pointer to the string
 *
 * Return: Nothing.
 */
void clearComments(char *buf)
{
	int index;

	index = 0;
	for (; buf[index] != '\0'; index++)
		if (buf[index] == '#' && (!index || buf[index - 1] == ' '))
		{
			buf[index] = '\0';
			break;
		}
}
