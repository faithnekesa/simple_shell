#include "shell.h"

/**
 * myExit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int myExit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = myErratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			myEputs(info->argv[1]);
			myEputchar('\n');
			return (1);
		}
		info->err_num = myErratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * myCd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int myCd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		myPuts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = getEnv(info, "HOME=");
		if (!dir)
			chdir_ret =
			chdir((dir = getEnv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (myStrcmp(info->argv[1], "-") == 0)
	{
		if (!getEnv(info, "OLDPWD="))
		{
			myPuts(s);
			myPutchar('\n');
			return (1);
		}
		myPuts(getEnv(info, "OLDPWD=")), myPutchar('\n');
		chdir_ret =
			chdir((dir = getEnv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		myEputs(info->argv[1]), myEputchar('\n');
	}
	else
	{
		setEnv(info, "OLDPWD", getEnv(info, "PWD="));
		setEnv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * myHelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int myHelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	myPuts("help call works. Function not yet implemented \n");
	if (0)
		myPuts(*arg_array);
	return (0);
}
