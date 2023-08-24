#include "shell.h"

/**
 * get_environ -Returns the string array copy of our environ
 * @info:Used to maintain constant function prototype
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unsetEnv -Removes an environment variable
 * @info:Used to maintain constant function prototype
 * @var: the string environment variable
 * Return: 1 on delete, 0 otherwise
 */
int unsetEnv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = startsWith(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * setEnv -Initializes or modifies  a new environment variable
 * @info:Used to maintain a constant function prototype
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int setEnv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(myStrlen(var) + myStrlen(value) + 2);
	if (!buf)
		return (1);
	myStrcpy(buf, var);
	myStrcat(buf, "=");
	myStrcat(buf, value);
	node = info->env;
	while (node)
	{
		p = startsWith(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
