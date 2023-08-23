#include "shell.h"

/**
 * interactiveShell -Function that returns true if the
 * shell is in interactive mode and false otherwise
 * @info:A struct for pointers
 * Return: 1 if shell kis in interactive mode and
 * 0 if otherwise
 */
int interactiveShell(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readFileDesc <= 2);
}
