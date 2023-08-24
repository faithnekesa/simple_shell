#include "shell.h"

/**
 * h_shell - main shell loop
 * @info: the pointer to struct
 * @av: the argument vector
 *
 * Return: 0 on success, 1 on error
 */
int h_shell(info_t *info, char **av)
{
	ssize_t rd = 0;
	int retcmd = 0;

	while (rd != -1 && retcmd != -2)
	{
		clearInfo(info);
		if (interactiveShell(info))
			myPuts("sf:)$ ");
		putcharError(BUFFER_FLUSH);
		rd = get_lineonly(info);
		if (rd != -1)
		{
			setInfo(info, av);
			retcmd = find_bcmd(info);
			if (retcmd == -1)
				find_pcmd(info);
		}
		else if (interactiveShell(info))
			myPutchar('\n');
		freeInfo(info, 0);
	}
	writeHistory(info);
	freeInfo(info, 1);
	if (!interactiveShell(info) && info->commandStatus)
		exit(info->commandStatus);
	if (retcmd == -2)
	{
		if (info->errorCode == -1)
			exit(info->commandStatus);
		exit(info->errorCode);
	}
	return (retcmd);
}
/**
 * find_bcmd - finds a builtin command in the shell
 * @info: the pointer to struct
 *
 * Return: -1 if builtin command not found,
 * 0 if builtin command executed successfully,
 * 1 if builtin command found but not successful,
 * 2 if builtin command  signals exit()
 */
int find_bcmd(info_t *info)
{
	int n = 0;
	int ret_bcmd = -1;
	builtin_table builtin_tbl[] = {
		{"exit", myExit},
		{"env", myEnv},
		{"help", myHelp},
		{"history", myHistory},
		{"setenv", mySetEnv},
		{"unsetenv", myUnsetEnv},
		{"cd", myChangeDir},
		{"alias", myAlias},
		{NULL, NULL}
	};

	for (; builtin_tbl[n].type; n++)
		if (_strcmp(info->argv[0], builtin_tbl[n].type) == 0)
		{
			info->lineCount++;
			ret_bcmd = builtin_tbl[n].func(info);
			break;
		}
	return (ret_bcmd);
}
/**
 * find_pcmd - finds a command in PATH
 * @info: the pointer to struct
 *
 * Return: Nothing.
 */
void find_pcmd(info_t *info)
{
	char *path = NULL;
	int index = 0;
	int n = 0;

	info->path = info->argv[0];
	if (info->lineCountFlag == 1)
	{
		info->lineCount++;
		info->lineCountFlag = 0;
	}
	for (; info->arg[index]; index++)
		if (!is_delim(info->arg[index], " \t\n"))
			n++;
	if (!n)
		return;

	path = findPath(info, mygetEnv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactiveShell(info) || mygetEnv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->commandStatus = 127;
			printError(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the pointer to struct
 *
 * Return: Nothing.
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			freeInfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->commandStatus));
		if (WIFEXITED(info->commandStatus))
		{
			info->commandStatus = WEXITSTATUS(info->commandStatus);
			if (info->commandStatus == 126)
				printError(info, "Permission denied\n");
		}
	}
}
