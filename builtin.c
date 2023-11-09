#include "shell.h"

/**
 * help_command - provides help information for built-in commands
 * @info: shell state, including arguments provided to the 'help' command
 *
 * Displays a message indicating that the help functionality is not yet implemented.
 * It serves as a placeholder for when the help descriptions are added.
 */
int _myhelp(info_t *info)
{
	_puts("Help functionality is underway. Please check back later.\n");
	if (0) // Temporary workaround for unused variable warning.
		_puts(*info->argv);
	return (0);
}

/**
 * change_directory - changes the shell's current directory
 * @info: shell state, including arguments provided to the 'cd' command
 *
 * Attempts to change the current directory based on the arguments provided.
 * If no argument is given, it tries to go to the home directory.
 * It can handle relative paths, absolute paths, and '-' for previous directory.
 */
int _mycd(info_t *info)
{
	char *current_dir, *target_dir, buffer[1024];
	int change_dir_result;

	current_dir = getcwd(buffer, sizeof(buffer));
	if (!current_dir)
		_puts("Error: getcwd failed.\n");

	target_dir = info->argv[1] ? info->argv[1] : _getenv(info, "HOME=");
	if (!target_dir)
		change_dir_result = chdir(current_dir); // Fallback to current directory if HOME is not set.
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		target_dir = _getenv(info, "OLDPWD=");
		_puts(target_dir ? target_dir : current_dir);
		_putchar('\n');
		change_dir_result = chdir(target_dir ? target_dir : current_dir);
	}
	else
		change_dir_result = chdir(target_dir);

	if (change_dir_result == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(target_dir), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, sizeof(buffer)));
	}
	return (0);
}

/**
 * exit_shell - exits the shell with a specified status code
 * @info: shell state, potentially including an exit status argument
 *
 * Processes the 'exit' command, extracting an optional exit status.
 * If no status is provided, exits with the current status of the shell.
 * If an invalid status is provided, prints an error and returns.
 */
int _myexit(info_t *info)
{
	int status_code;

	if (info->argv[1]) // Check for an argument to the exit command.
	{
		status_code = _erratoi(info->argv[1]);
		if (status_code == -1) // Validate the provided argument.
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = status_code;
		return (-2); // Signal to exit the shell.
	}
	info->err_num = -1;
	return (-2); // Signal to exit the shell with the last command's status.
}
