#include "shell.h"

/**
 * start_shell - initiates the simple shell program
 * @ac: the count of command-line arguments
 * @av: the array of command-line arguments
 *
 * Initializes the shell's info structure and processes command-line arguments.
 * If a script file is provided, it attempts to open and read from it.
 * Initializes the shell environment, loads history, and starts the shell loop.
 * Exits with appropriate status codes upon encountering file access errors.
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	// Inline assembly for demonstration purposes, not typically used in high-level applications.
	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2) // If there's a file argument, attempt to open it for reading.
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1) // If file opening fails, handle the error appropriately.
		{
			if (errno == EACCES)
				exit(126); // Exit with code 126 for permission denied.
			if (errno == ENOENT)
			{
				// Print an error message if the file doesn't exist.
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127); // Exit with code 127 for file not found.
			}
			return (EXIT_FAILURE); // General failure exit code.
		}
		info->readfd = fd; // Set the read file descriptor in the info structure.
	}
	populate_env_list(info); // Initialize the environment list.
	read_history(info); // Load the shell history.
	hsh(info, av); // Start the shell's main loop.
	return (EXIT_SUCCESS); // Successful exit code.
}
