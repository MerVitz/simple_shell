#include "shell.h"

/**
 * help_command - provides help information for built-in commands
 * @info: shell state, including arguments provided to the 'help' command
 *
 * Displays a message indicating that the help functionality is
 * not yet implemented.
 * Return: serves as a placeholder for when the help descriptions are added.
 */
int help_command(info_t *info)
{
	puts("Help functionality is underway. Please check back later.\n");
	if (0)
		puts(*info->argv);
	return (0);
}

/**
 * change_directory - changes the shell's current directory
 * @info: shell state, including arguments provided to the 'cd' command
 *
 * Attempts to change the current directory based on the arguments provided.
 * If no argument is given, it tries to go to the home directory.
 * Return: can handle relative paths, absolute paths,
 * and '-' for previous directory.
 */
int change_directory(info_t *info)
{
	char *current_dir, *target_dir, buffer[1024];
	int change_dir_result;

	current_dir = getcwd(buffer, sizeof(buffer));
	if (!current_dir)
		puts("Error: getcwd failed.\n");

	target_dir = info->argv[1] ? info->argv[1] : getenv(info, "HOME=");
	if (!target_dir)
		change_dir_result = chdir(current_dir);
	else if (strcmp(info->argv[1], "-") == 0)
	{
		target_dir = getenv(info, "OLDPWD=");
		puts(target_dir ? target_dir : current_dir);
		putchar('\n');
		change_dir_result = chdir(target_dir ? target_dir : current_dir);
	}
	else
		change_dir_result = chdir(target_dir);

	if (change_dir_result == -1)
	{
		print_error(info, "can't cd to ");
		puts(target_dir), putchar('\n');
	}
	else
	{
		setenv(info, "OLDPWD", getenv(info, "PWD="));
		setenv(info, "PWD", getcwd(buffer, sizeof(buffer)));
	}
	return (0);
}

/**
 * exit_shell - exits the shell with a specified status code
 * @info: shell state, potentially including an exit status argument
 *
 * Processes the 'exit' command, extracting an optional exit status.
 * If no status is provided, exits with the current status of the shell.
 * Return: If an invalid status is provided,
 * prints an error and returns.
 */
int exit_shell(info_t *info)
{
	int status_code;

	if (info->argv[1])
	{
		status_code = _erratoi(info->argv[1]);
		if (status_code == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			puts(info->argv[1]);
			putchar('\n');
			return (1);
		}
		info->err_num = status_code;
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
