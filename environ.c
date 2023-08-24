#include "shell.h"

/**
 * *get_environ - returns the string array copy of our environ
 * @info: structure with arguments to maintain prototype functions
 *
 * Return: Always 0.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->envChanged)
	{
		info->environ = list_elements(info->env);
		info->envChanged = 0;
	}
	return (info->environ);
}
/**
 * _myset_env - Modifies an existing or initilizes a new environment variable
 * @info: structure with arguments to maintain prototype functions
 * @envar: String environment variable
 * @envalue: String environment value
 *
 * Return: Always 0
 */
int _myset_env(info_t *info, char *envar, char *envalue)
{
	char *ptrenv;
	list_t *node;
	char *buf = NULL;

	if (envar == NULL || envalue == NULL)
	{
		return (0);
	}
	buf = malloc(_strlen(envar) + _strlen(envalue) + 2);
	if (buf == NULL)
	{
		return (1);
	}
	_strcpy(buf, envar);
	_strcat(buf, "=");
	_strcat(buf, envalue);
	node = info->env;
	while (node != NULL)
	{
		ptrenv = begin_with(node->str, envar);
		if (ptrenv && *ptrenv == '=')
		{
			free(node->str);
			node->str = buf;
			info->envChanged = 1;
			return (0);
		}
	}
	node = node->next;
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->envChanged = 1;
	return (0);
}

/**
 * _mydel_env - deletes an environment variable
 * @info: structure with arguments to maintain prototype functions
 * @envar: String environment variable
 *
 * Return: 1 on delete, 0 on failure
 */
int _mydel_env(info_t *info, char *envar)
{
	char *ptrenv;
	list_t *node = info->env;
	int m;

	if ((!node) || (!envar))
	{
		return (0);
	}
	while (node != NULL)
	{
		ptrenv = begin_with(node->str, envar);
		if (ptrenv && *ptrenv == '=')
		{
			info->envChanged = delete_node(&(info->env), m);
			m = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		m++;
	}
	return (info->envChanged);
}
