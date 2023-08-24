#include "shell.h"

/**
 * findPath -A function that finds cmd in the PATH string
 * @info:The struct for info
 * @pathStr:The string path
 * @cmd:The cmd being searched for
 * Return:The full cmd path if found, NULL otherwise
 */
char *findPath(info_t *info, char *pathStr, char *cmd)
{
	int counter = 0, curr_pos = 0;
	char *path;

	if (!pathStr)
		return (NULL);
	if ((_strlen(cmd) > 2) && begin_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathStr[counter] || pathStr[counter] == ':')
		{
			path = duplicateChars(pathStr, curr_pos, counter);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathStr[counter])
				break;
			curr_pos = counter;
		}
		counter++;
	}
	return (NULL);
}

/**
 * is_cmd -A function that checks if a file is executable or not
 * @info:The struct for info
 * @path:The file path
 * Return: 1 if true and 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat str;

	(void)info;
	if (!path || stat(path, &str))
		return (0);

	if (str.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicateChars -A function that duplicates chars
 * @pathStr: the PATH string
 * @start:The initial index
 * @stop: The last index
 * Return:A pointer to the new buffer
 */
char *duplicateChars(char *pathStr, int start, int stop)
{
	static char buf[1024];
	int counter = 0, counter2 = 0;

	for (counter2 = 0, counter = start; counter < stop; counter++)
		if (pathStr[counter] != ':')
			buf[counter2++] = pathStr[counter];
	buf[counter2] = 0;
	return (buf);
}
