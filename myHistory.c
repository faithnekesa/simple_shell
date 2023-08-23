#include "shell.h"

/**
 * writeHistory - creates a file
 * @info: The address of the struct
 *
 * Return: 1 on success, -1 otherwise
 */
int writeHistory(info_t *info)
{
	ssize_t op;
	char *newline = (char *)'\n';
	char *name = getHistory(info);
	char *bufferFlush = (char *)BUFFER_FLUSH;
	list_t *node = NULL;

	if (!name)
	{
		return (-1);
	}
	op = open(name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(name);
	if (op == -1)
	{
		return (-1);
	}
	for (node = info->history; node; node = node->next)
	{
		myPutsfileDesc(node->str, op);
		myPutsfileDesc(newline, op);
	}
	myPutsfileDesc(bufferFlush, op);
	close(op);
	return (1);
}
/**
 * readHistory - reads a file
 * @info: The address of the struct
 *
 * Return: historyLineCount(history count) on success, 0 otherwise
 */
int readHistory(info_t *info)
{
	int index = 0, n = 0, lc = 0;
	ssize_t op, rd, byte = 0;
	struct stat st;
	char *newnode = NULL, *name = getHistory(info);

	if (!name)
		return (0);

	op = open(name, O_RDONLY);
	free(name);
	if (op == -1)
		return (0);
	if (!fstat(op, &st))
		byte = st.st_size;
	if (byte < 2)
		return (0);
	newnode = malloc(sizeof(char) * (byte + 1));
	if (!newnode)
		return (0);
	rd = read(op, newnode, byte);
	newnode[byte] = 0;
	if (rd <= 0)
		return (free(newnode), 0);
	close(op);
	for (; index < byte; index++)
		if (newnode[index] == '\n')
		{
			newnode[index] = 0;
			createHistoryList(info, newnode + n, lc++);
			n = index + 1;
		}
	if (n != index)
		createHistoryList(info, newnode + n, lc++);
	free(newnode);
	info->historyLineCount = lc;
	while (info->historyLineCount-- >= _HISTORY_MAX)
		delete_node(&(info->history), 0);
	renumberHistory(info);
	return (info->historyLineCount);
}
/**
 * createHistoryList - adds entry to a history linked list
 * @info: The address of the struct
 * @buf: buffer in commandline
 * @lc: the history linecount
 *
 * Return: Always 0
 */
int createHistoryList(info_t *info, char *buf, int lc)
{
	list_t *newnode = NULL;

	if (info->history)
		newnode = info->history;
	add_node_end(&newnode, buf, lc);

	if (!info->history)
		info->history = newnode;
	return (0);
}
/**
 * renumberHistory - renumbers the history list
 * @info: The address of the struct
 *
 * Return: new historyLineCount
 */
int renumberHistory(info_t *info)
{
	list_t *newnode = info->history;
	int index;

	index = 0;
	while (newnode != NULL)
	{
		newnode->num = index++;
		newnode = newnode->next;
	}
	return (info->historyLineCount = index);
}
/**
 * *getHistory - gets the history file
 * @info: The address of the struct
 *
 * Return: pointer to buffer
 */

char *getHistory(info_t *info)
{
	char *str, *ptr;

	ptr = mygetEnv(info, "HOME=");
	if (!ptr)
	{
		return (NULL);
	}
	str = malloc(sizeof(char) * (_strlen(ptr) + _strlen(_HISTORY_FILE) + 2));
	if (!str)
	{
		return (NULL);
	}
	str[0] = 0;
	_strcpy(str, ptr);
	_strcat(str, "/");
	_strcat(str, _HISTORY_FILE);
	return (str);
}
