#include "shell.h"

/**
 * myChangeDir -A function that changes the
 * current directory of the process
 * @info:Struct to hold the arguments that will be
 * keyed in terminal
 * Return:0 always
 */
int myChangeDir(info_t *info)
{
	char *newstr, *dir, buffer[1024];
	int chdir_ret;

	newstr = getcwd(buffer, 1024);
	if (!newstr)
		myPuts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = mygetEnv(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = mygetEnv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!mygetEnv(info, "OLDPWD="))
		{
			myPuts(newstr);
			myPutchar('\n');
			return (1);
		}
		myPuts(mygetEnv(info, "OLDPWD=")), myPutchar('\n');
		chdir_ret =
			chdir((dir = mygetEnv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		printError(info, "can't cd to ");
		putsError(info->argv[1]), putcharError('\n');
	}
	else
	{
		_myset_env(info, "OLDPWD", mygetEnv(info, "PWD="));
		_myset_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * myExit -A function that exits the shell
 * @info:Struct to hold the arguments that will be
 * keyed in terminal
 * Return: 0 if info.argv[0] is not equal to exit
 */
int myExit(info_t *info)
{
	int checkExit;

	if (info->argv[1])
	{
		checkExit = atoiError(info->argv[1]);
		if (checkExit == -1)
		{
			info->commandStatus = 2;
			printError(info, "Illegal number: ");
			putsError(info->argv[1]);
			putcharError('\n');
			return (1);
		}
		info->errorCode = atoiError(info->argv[1]);
		return (-2);
	}
	info->errorCode = -1;
	return (-2);
}

/**
 * myHelp -A function that hanges the current directory of a process
 * @info:Struct to hold the arguments that will be
 * keyed in terminal
 * Return: Always 0
 */
int myHelp(info_t *info)
{
	char **arrayArg;

	arrayArg = info->argv;
	myPuts("help call works. Function not yet implemented \n");
	if (0)
		myPuts(*arrayArg);
	return (0);
}
