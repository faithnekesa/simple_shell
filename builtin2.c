#include "shell.h"

/**
 * myHistory -A function that displays the historical
 * commands alongside line numbers
 * @info:Struct to hold the arguments that will be
 * keyed in terminal
 * Return:0 always
 */
int myHistory(info_t *info)
{
	printList(info->history);
	return (0);
}

/**
 * setAlias -A function that sets an alias to a string
 * @info:Struct to hold the arguments that will be
 * keyed in terminal
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int setAlias(info_t *info, char *str)
{
	char *strPtr;

	strPtr = _strchr(str, '=');
	if (!strPtr)
		return (1);
	if (!*++strPtr)
		return (unsetAlias(info, str));

	unsetAlias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * unsetAlias -A function that sets alias to a string
 * @info:Struct to hold the arguments that will be
 * keyed in terminal
 * @str: String alias
 * Return:0 on success and 1 on error
 */
int unsetAlias(info_t *info, char *str)
{
	char *strPtr, strC;
	int retN;

	strPtr = _strchr(str, '=');
	if (!strPtr)
		return (1);
	strC = *strPtr;
	*strPtr = 0;
	retN = delete_node(&(info->alias),
		node_index(info->alias, node_prefix(info->alias, str, -1)));
	*strPtr = strC;
	return (retN);
}

/**
 * myAlias -A function that mimics the alias  builtin
 * @info:A struct to hold the arguments that will be
 * keyed in terminal
 * Return: Always 0
 */
int myAlias(info_t *info)
{
	int counter = 0;
	char *strPtr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			printAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (counter = 1; info->argv[counter]; counter++)
	{
		strPtr = _strchr(info->argv[counter], '=');
		if (strPtr)
			setAlias(info, info->argv[counter]);
		else
			printAlias(node_prefix(info->alias, info->argv[counter], '='));
	}

	return (0);
}

/**
 * printAlias -A function that prints an alias string
 * @node:Alias node
 * Return: Always 0 on success, 1 on error
 */
int printAlias(list_t *node)
{
	char *strPtr = NULL, *aliasNode = NULL;

	if (node)
	{
		strPtr = _strchr(node->str, '=');
		for (aliasNode = node->str; aliasNode <= strPtr; aliasNode++)
		myPutchar(*aliasNode);
		myPutchar('\'');
		myPuts(strPtr + 1);
		myPuts("'\n");
		return (0);
	}
	return (1);
}
