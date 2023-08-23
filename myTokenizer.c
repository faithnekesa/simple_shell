#include "shell.h"

/**
 * **myStrtok -A function that splits a string into words
 * @str: the string input being split
 * @d:The string delimeter
 * Return:An array string pointer, NULL on failure
 */

char **myStrtok(char *str, char *d)
{
	int counter, counter2, counter3, counter4, wordNum = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (counter = 0; str[counter] != '\0'; counter++)
		if (!is_delim(str[counter], d) && (is_delim(str[counter + 1],
						d) || !str[counter + 1]))
			wordNum++;

	if (wordNum == 0)
		return (NULL);
	s = malloc((1 + wordNum) * sizeof(char *));
	if (!s)
		return (NULL);
	for (counter = 0, counter2 = 0; counter2 < wordNum; counter2++)
	{
		while (is_delim(str[counter], d))
			counter++;
		counter3 = 0;
		while (!is_delim(str[counter + counter3], d) && str[counter + counter3])
			counter3++;
		s[counter2] = malloc((counter3 + 1) * sizeof(char));
		if (!s[counter2])
		{
			for (counter3 = 0; counter3 < counter2; counter3++)
				free(s[counter3]);
			free(s);
			return (NULL);
		}
		for (counter4 = 0; counter4 < counter3; counter4++)
			s[counter2][counter4] = str[counter++];
		s[counter2][counter4] = 0;
	}
	s[counter2] = NULL;
	return (s);
}

/**
 * **myStrtok2 -A function that splits a string into words
 * @str: the string input being split
 * @d:The string delimeter
 * Return:An array string pointer, NULL on failure
 */
char **myStrtok2(char *str, char d)
{
	int counter, counter2, counter3, counter4, wordNum = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (counter = 0; str[counter] != '\0'; counter++)
		if ((str[counter] != d && str[counter + 1] == d) ||
				    (str[counter] != d && !str[counter + 1]) || str[counter + 1] == d)
			wordNum++;
	if (wordNum == 0)
		return (NULL);
	s = malloc((1 + wordNum) * sizeof(char *));
	if (!s)
		return (NULL);
	for (counter = 0, counter2 = 0; counter2 < wordNum; counter2++)
	{
		while (str[counter] == d && str[counter] != d)
			counter++;
		counter3 = 0;
		while (str[counter + counter3] != d && str[counter + counter3] &&
				str[counter + counter3] != d)
			counter3++;
		s[counter2] = malloc((counter3 + 1) * sizeof(char));
		if (!s[counter2])
		{
			for (counter3 = 0; counter3 < counter2; counter3++)
				free(s[counter3]);
			free(s);
			return (NULL);
		}
		for (counter4 = 0; counter4 < counter3; counter4++)
			s[counter2][counter4] = str[counter++];
		s[counter2][counter4] = 0;
	}
	s[counter2] = NULL;
	return (s);
}
