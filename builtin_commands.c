#include "shell.h"

/**
 * _myexit - exits the shell with a specified status code
 * @info: shell state, potentially including an exit status argument
 *
 * Processes the 'exit' command, extracting an optional exit status.
 * If no status is provided, exits with the current status of the shell.
 * Return: If an invalid status is provided,
 * prints an error and returns.
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal Number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the shell's current directory
 * @info: shell state, including arguments provided to the 'cd' command
 *
 * Attempts to change the current directory based on the arguments provided.
 * If no argument is given, it tries to go to the home directory.
 * Return: can handle relative paths, absolute paths,
 * and '-' for previous directory.
 */
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - provides help information for built-in commands
 * @info: shell state, including arguments provided to the 'help' command
 *
 * Displays a message indicating that the help functionality is
 * not yet implemented.
 * Return: serves as a placeholder for when the help descriptions are added.
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("Help Functionality Is Underway. Please Check Back Later. \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
