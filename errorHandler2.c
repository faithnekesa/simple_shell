#include "shell.h"

/**
 * printError -A function that prints an error message to terminal
 * @info:The return info struct
 * @errorStr: string containing specified error type
 * Return:The converted string, 0 if the string has no numbers
 * and -1 on error
 */
void printError(info_t *info, char *errorStr)
{
	putsError(info->fileName);
	putsError(": ");
	printDecimal(info->lineCount, STDERR_FILENO);
	putsError(": ");
	putsError(info->argv[0]);
	putsError(": ");
	putsError(errorStr);
}

/**
 * atoiError -A function that converts a string to an integer
 * @s: the string being converted to int
 * Return:Converted number,0 if the string has no number and -1 on error
 */
int atoiError(char *s)
{
	int counter = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (counter = 0;  s[counter] != '\0'; counter++)
	{
		if (s[counter] >= '0' && s[counter] <= '9')
		{
			result *= 10;
			result += (s[counter] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * convert_number -This is a converter function that cones atoi
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n1 = num;

	if (!(flags & _CONVERT_LOWERCASE) && num < 0)
	{
		n1 = -num;
		sign = '-';

	}
	array = flags & _CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n1 % base];
		n1 /= base;
	} while (n1 != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * printDecimal - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fileDesc: the filedescriptor to write to
 * Return: number of characters printed
 */
int printDecimal(int input, int fileDesc)
{
	int (*myPutchar)(char) = myPutchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fileDesc == STDERR_FILENO)
		myPutchar = putcharError;
	if (input < 0)
	{
		_abs_ = -input;
		myPutchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			myPutchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	myPutchar('0' + current);
	count++;

	return (count);
}
