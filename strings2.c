#include "shell.h"

/**
 * myPuts -A function that prints an input string from stdin
 * @str:the string to be printed
 * Return:nothing.
 */
void myPuts(char *str)
{
	int counter = 0;

	if (!str)
		return;
	while (str[counter] != '\0')
	{
		myPutchar(str[counter]);
		counter++;
	}
}

/**
 * myPutchar -A function that writes a character to stdout
 * @c: The character being printed
 * Return:1 on success, -1 on error and errno is set
 */
int myPutchar(char c)
{
	static int counter;
	static char buf[BUF_SIZE_WRITER];

	if (c == BUFFER_FLUSH || counter >= BUF_SIZE_WRITER)
	{
		write(1, buf, counter);
		counter = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[counter++] = c;
	return (1);
}
