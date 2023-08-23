#include "shell.h"

/**
 * putFileDesc -A function that writes the char inputChar
 * to the given file descriptor
 * @inputChar: The character being printed
 * @fileDesc: The filedescriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int putFileDesc(char inputChar, int fileDesc)
{
	static int counter;
	static char buf[BUF_SIZE_WRITER];

	if (inputChar == BUFFER_FLUSH || counter >= BUF_SIZE_WRITER)
	{
		write(fileDesc, buf, counter);
		counter = 0;
	}
	if (inputChar != BUFFER_FLUSH)
		buf[counter++] = inputChar;
	return (1);
}

/**
 * myPutsfileDesc -A function that prints an input string
 * @str:The tring to be printed
 * @fileDesc: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int myPutsfileDesc(char *str, int fileDesc)
{
	int counter = 0;

	if (!str)
		return (0);
	while (*str)
	{
		counter += putFileDesc(*str++, fileDesc);
	}
	return (counter);
}

/**
 * putsError -A function that prints a string
 * @str:String being printed
 * Return: Nothing
 */
void putsError(char *str)
{
	int counter = 0;

	if (!str)
		return;
	while (str[counter] != '\0')
	{
		putcharError(str[counter]);
		counter++;
	}
}

/**
 * putcharError -A function that writes the character str to stderr
 * @str:Character being printed
 * Return:1 on success, -1 on error,error code is set appropriately
 */
int putcharError(char str)
{
	static int counter;
	static char buf[BUF_SIZE_WRITER];

	if (str == BUFFER_FLUSH || counter >= BUF_SIZE_WRITER)
	{
		write(2, buf, counter);
		counter = 0;
	}
	if (str != BUFFER_FLUSH)
		buf[counter++] = str;
	return (1);
}
