#include "shell.h"

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: difference between the two strings
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	if (*s1 == *s2)
	{

		return (0);
	}
	else
	{
		return (*s1 < *s2 ? -1 : 1);
	}
}

/**
 * *_strcat - concatenates two strings
 * @dest: pointer to string to be concatenated
 * @src: string source
 *
 * Return: pointer to destination @dest
 */
char *_strcat(char *dest, char *src)
{
	int string1 = 0;
	int string2 = 0;

	while (*(dest + string1) != '\0')
		string1++;
	while (string2 >= 0)
	{
		*(dest + string1) = *(src + string2);
		if (*(src + string2) == '\0')
			break;
		string1++;
		string2++;
	}
	return (dest);
}

/**
 * _strlen - returns the length of a string
 * @str: pointer to a string
 *
 * Return: length of string
 */

size_t _strlen(char *str)
{
	size_t length = 0;

	while (*str++)
		length++;

	return (length);
}

/**
 * begin_with - checks if needle starts with haystack
 * @haystack: string to  be searched
 * @needle: Substring to be treated
 *
 * Return: address of next char of haystack, NULL if haystack is not found
 */
char *begin_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
		{
			return (NULL);
		}
	}
	return ((char *)haystack);
}
