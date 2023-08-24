#include "shell.h"
#include <stddef.h>

/**
 * *_strchr - locates a character
 * @s: string to be treated
 * @c: character to be located
 *
 * Return: pointer to first occurrence of c and NULL if not found
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * *_strncpy - copies a string
 * @dest: string destination
 * @src: string source
 * @n: number of bytes
 *
 * Return: destination @dest
 */

char *_strncpy(char *dest, char *src, int n)
{
	int letters = 0;
	int cpletters;
	char *str = dest;

	while (src[letters] != '\0' && letters < n - 1)
	{
		dest[letters] = src[letters];
		letters++;
	}
	if (letters < n)
	{
		cpletters = letters;
		while (cpletters < n)
		{
			dest[cpletters] = '\0';
			cpletters++;
		}
	}
	return (str);
}

/**
 * *_strncat - concatenates two strings
 * @dest: First  string
 * @src: Second string
 * @n: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int string1 = 0;
	int string2 = 0;
	char *str = dest;

	while (dest[string1] != '\0')
	{
		string1++;
	}
	while (src[string2] != '\0' && string2 < n)
	{
		dest[string1] = src[string2];
		string1++;
		string2++;
	}
	if (string2 < n)
	{
		dest[string1] = '\0';
	}
	return (str);
}
