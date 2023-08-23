#include "shell.h"

/**
 * changeVars - change variables of a tokenized string
 * @info: The address of the struct
 *
 * Return: 1 on success, 0 otherwise
 */
int changeVars(info_t *info)
{
	int index;
	list_t *node;

	index = 0;
	for (; info->argv[index]; index++)
	{
		if (info->argv[index][0] != '$' || !info->argv[index][1])
			continue;
		if (!_strcmp(info->argv[index], "$?"))
		{
			changeString(&(info->argv[index]),
					_strdup(convert_number(info->commandStatus, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[index], "$$"))
		{
			changeString(&(info->argv[index]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_prefix(info->env, &info->argv[index][1], '=');
		if (node)
		{
			changeString(&(info->argv[index]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		changeString(&info->argv[index], _strdup(""));

	}
	return (0);
}
/**
 * changeString - changes string to another
 * @p: address of string to be changed
 * @str: changed string
 *
 * Return: 1 on success, 0 otherwise
 */
int changeString(char **p, char *str)
{
	free(*p);
	*p = str;
	return (1);
}
/**
 * changeAlias - change aliases in the tokenized string
 * @info: The address of the struct
 *
 * Return: 1 on success, 0 otherwise
 */
int changeAlias(info_t *info)
{
	int index;
	list_t *node;
	char *ptr;

	index = 0;
	for (; index < 10; index++)
	{
		node = node_prefix(info->alias, info->argv[0], '=');
		if (!node)
		{
			return (0);
		}
		free(info->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
		{
			return (0);
		}
		ptr = _strdup(ptr + 1);
		if (!ptr)
		{
			return (0);
		}
		info->argv[0] = ptr;
	}
	return (1);
}
/**
 * isChain - tests a buffer if it is a chain delimeter
 * @info: The address of the struct
 * @s: A string
 * @ptr: address of buf
 *
 * Return: 1 on success, 0 otherwise
 */
int isChain(info_t *info, char *s, size_t *ptr)
{
	size_t index;

	index = *ptr;
	if (s[index] == '|' && s[index + 1] == '|')
	{
		s[index] = 0;
		index++;
		info->cmdBufferType = _CMD_OR;
	}
	else if (s[index] == '&' && s[index + 1] == '&')
	{
		s[index] = 0;
		index++;
		info->cmdBufferType = _CMD_AND;
	}
	else if (s[index] == ';')
	{
		s[index] = 0;
		info->cmdBufferType = _CMD_CHAIN;
	}
	else
		return (0);
	*ptr = index;
	return (1);
}

/**
 * check_chain - checks a string with chain commands
 * @info: The address of the struct
 * @s: A string
 * @ptr: address of string
 * @index: starting position in buf
 * @len: length of string
 *
 * Return: Nothing.
 */
void check_chain(info_t *info, char *s, size_t *ptr, size_t index, size_t len)
{
	size_t str;

	str = *ptr;
	if (info->cmdBufferType == _CMD_AND)
	{
		if (info->commandStatus)
		{
			s[index] = 0;
			str = len;
		}
	}
	if (info->cmdBufferType == _CMD_OR)
	{
		if (!info->commandStatus)
		{
			s[index] = 0;
			str = len;
		}
	}

	*ptr = str;
}
