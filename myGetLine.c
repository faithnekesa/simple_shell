#include "shell.h"

/**
 * my_getline - gets the line of input from STDIN
 * @info: The address of the struct
 * @ptr: address of pointer to buffer(input)
 * @length: size of ptr
 *
 * Return: size of ptr
 */
int my_getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[BUF_SIZE_READER];
	static size_t n, len;
	size_t m;
	ssize_t string_t = 0, sizebuf = 0;
	char *str1 = NULL, *str2 = NULL, *p;

	str1 = *ptr;
	if (str1 && length)
		sizebuf = *length;
	if (n == len)
		n = len = 0;
	string_t = print_buf(info, buf, &len);
	if (string_t == -1 || (string_t == 0 && len == 0))
		return (-1);
	p = _strchr(buf + n, '\n');
	m = p ? 1 + (unsigned int)(p - buf) : len;
	str2 = _realloc(str1, sizebuf, sizebuf ? sizebuf + m : m + 1);
	if (!str2)
		return (str1 ? free(str1), -1 : -1);

	if (sizebuf)
		_strncat(str2, buf + n, m - n);
	else
		_strncpy(str2, buf + n, m - n + 1);

	sizebuf += m - n;
	n = m;
	str1 = str2;
	if (length)
		*length = sizebuf;
	*ptr = str2;
	return (sizebuf);
}
/**
 * signal_check - blocks ctrl-C
 * @n: number of signals
 *
 * Return: Nothing.
 */
void signal_check(__attribute__((unused))int n)
{
	myPuts("\n");
	myPuts("$ ");
	myPutchar(BUFFER_FLUSH);
}
/**
 * print_buf - reads a buffer
 * @info: The address of the struct
 * @buf: buffer(input)
 * @n: size of buf
 *
 * Return: the read buffer
 */
ssize_t print_buf(info_t *info, char *buf, size_t *n)
{
	ssize_t rd;

	rd = 0;
	if (*n)
	{
		return (0);
	}
	rd = read(info->readFileDesc, buf, BUF_SIZE_READER);
	if (rd >= 0)
	{
		*n = rd;
	}
	return (rd);
}
/**
 * get_lineonly - gets a line without the newline
 * @info: The address of the struct
 *
 * Return: length of buffer
 */
ssize_t get_lineonly(info_t *info)
{
	static char *buf;
	static size_t index, c, len;
	ssize_t rd = 0;
	char **ptrbuf = &(info->arg), *ptrstr;

	myPutchar(BUFFER_FLUSH);
	rd = input_buffer(info, &buf, &len);
	if (rd == -1)
		return (-1);
	if (len)
	{
		c = index;
		ptrstr = buf + index;

		check_chain(info, buf, &c, index, len);
		while (c < len)
		{
			if (isChain(info, buf, &c))
				break;
			c++;
		}

		index = c + 1;
		if (index >= len)
		{
			index = len = 0;
			info->cmdBufferType = _CMD_NORM;
		}

		*ptrbuf = ptrstr;
		return (_strlen(ptrstr));
	}
	*ptrbuf = buf;
	return (rd);
}
/**
 * input_buffer - buffer chained commands
 * @info: The address of the struct
 * @buf: address of buf
 * @length: pointer to len
 *
 * Return: size of buf
 */
ssize_t input_buffer(info_t *info, char **buf, size_t *length)
{
	ssize_t rd = 0;
	size_t m = 0;

	if (!*length)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, signal_check);
#if CHOOS_GETLINE
		rd = getline(buf, &m, stdin);
#else
		rd = my_getline(info, buf, &m);
#endif
		if (rd > 0)
		{
			if ((*buf)[rd - 1] == '\n')
			{
				(*buf)[rd - 1] = '\0';
				rd--;
			}
			info->lineCountFlag = 1;
			clearComments(*buf);
			createHistoryList(info, *buf, info->historyLineCount++);
			{
				*length = rd;
				info->cmdBuffer = buf;
			}
		}
	}
	return (rd);
}
