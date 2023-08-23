#include "shell.h"

/**
 * setInfo -A function that initializes info_t struct
 * @info:The address of the struct
 * @av:The argument array
 */
void setInfo(info_t *info, char **av)
{
	int counter = 0;

	info->fileName = av[0];
	if (info->arg)
	{
		info->argv = myStrtok(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (counter = 0; info->argv && info->argv[counter]; counter++)
			;
		info->argc = counter;

		changeAlias(info);
		changeVars(info);
	}
}

/**
 * clearInfo -A function that initializes the struct infor_t
 * @info:The address of the struct
 */
void clearInfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}


/**
 * freeInfo - frees info_t struct fields
 * @info:The address of the struct
 * @all:If all fields are freed, will be true
 */
void freeInfo(info_t *info, int all)
{
	s_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmdBuffer)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		s_free(info->environ);
			info->environ = NULL;
		p_free((void **)info->cmdBuffer);
		if (info->readFileDesc > 2)
			close(info->readFileDesc);
		myPutchar(BUFFER_FLUSH);
	}
}
