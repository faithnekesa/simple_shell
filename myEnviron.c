#include "shell.h"

/**
 * myEnv -prints the current environment
 * @info: Maintains a constant function prototype
 * Return: Always 0
 */
int myEnv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * getEnv - gets the value of an environ variable
 * @info:Used to maintain contant function prototype
 * @name: environment var name
 * Return: the value
 */
char *getEnv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = startsWith(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * mysetEnv -Initializes or modfies an environment var
 * @info:Used to maintain constant function prototype
 * Return: Always 0
 */
int mysetEnv(info_t *info)
{
	if (info->argc != 3)
	{
		myEputs("Incorrect number of arguements\n");
		return (1);
	}
	if (setEnv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * myunsetEnv - Remove an environment variable
 * @info:Used to maintain constant function prototype
 * Return: Always 0
 */
int myunsetEnv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		myEputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unsetEnv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info:Used to maintain constant function prototype
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
