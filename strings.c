#include "shell.h"

/**
 * is_alpha - checks for characters that are alphabets
 * @c: character to be treated
 *
 * Return: 1 if alphabetic, 0 otherwise.
 */
int is_alpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * is_delim - checks for characters that are delimeters
 * @c: character to be checked
 * @str: delimeter string
 *
 * Return: 1 if true, 0 if false.
 */
int is_delim(char c, char *str)
{
	while (*str)
	{
		if (*str++ == c)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * _atoi - converts a srting to an integer
 * @s: string to be converted
 *
 * Return: integer of the string
 */
int _atoi(char *s)
{
	int minus = 1;
	int flag = 0;
	int output;
	int index = 0;
	unsigned int result = 0;

	while (s[index] != '\0' && flag != 2)
	{
		if (s[index] == '-')
			minus *= -1;
		else if (s[index] >= '0' && s[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
		index++;
	}
	if (minus == -1)
		output = -result;
	else
		output = result;
	return (output);
}
/**
 * *_strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int index = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = 0;
	return (dest);
}
