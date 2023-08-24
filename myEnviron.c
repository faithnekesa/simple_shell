#include "shell.h"

/**
 * myEnv -A function that prints the current environment
 * @info:Struct to hold the arguments that will be
 * keyed in terminal
 * Return: Always 0
 */
int myEnv(info_t *info)
{
	printListStr(info->env);
	return (0);
}

/**
 * createEnvList -A function that populates env linked list
 * @info:@info:Struct to hold the arguments that will be
 * keyed in terminal
 * Return: Always 0
 */
int createEnvList(info_t *info)
{
	list_t *node = NULL;
	size_t counter;

	for (counter = 0; environ[counter]; counter++)
		add_node_end(&node, environ[counter], 0);
	info->env = node;
	return (0);
}

/**
 * mySetEnv -A function that initializes a new env variable
 * or modifies an existing variable
 * @info:Struct to hold the arguments that will be
 * keyed in terminal
 * Return:0 always
 */
int mySetEnv(info_t *info)
{
	if (info->argc != 3)
	{
		putsError("Number of args incorrect\n");
		return (1);
	}
	if (_myset_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * mygetEnv -A function that gets the value of an env variable
 * @info:Struct to hold the arguments that will be
 * keyed in terminal
 * @name: env var name
 *
 * Return: the value
 */
char *mygetEnv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = begin_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * myUnsetEnv -A function that removes an environment variable
 * @info:Struct to hold the arguments that will be
 * keyed in terminal
 * Return: Always 0
 */
int myUnsetEnv(info_t *info)
{
	int counter;

	if (info->argc == 1)
	{
		putsError("Too few arguements for the command\n");
		return (1);
	}
	for (counter = 1; counter <= info->argc; counter++)
		_mydel_env(info, info->argv[counter]);

	return (0);
}
