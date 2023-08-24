#include <stdio.h>
#include <stdlib.h>

#include "shell.h"

/**
 * main -The entry point of the program
 * @ac:The arg count
 * @av:The arg array
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
info_t info[] = { INFO_INIT };
int fileDesc = 2;


	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fileDesc)
			: "r" (fileDesc));

	if (ac == 2)
	{
		fileDesc = open(av[1], O_RDONLY);
		if (fileDesc == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				putsError(av[0]);
				putsError(": 0: Unable to open ");
				putsError(av[1]);
				putcharError('\n');
				putcharError(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readFileDesc = fileDesc;
	}
	createEnvList(info);
	readHistory(info);
	h_shell(info, av);
	return (EXIT_SUCCESS);
}
