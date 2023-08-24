#include "shell.h"

/* global variable for ^C handling */
unsigned int sig_flag;

/*
 * sig_handler - handles ^C signal interupt
 * @uv: unused variable (required for signal function prototype)
 * Return: void
 */


static void sig_handler(int uv)
{
	(void) uv;
	if (sig_flag == 0)
		_puts("\n$ ");
	else
		_puts("\n");
}

/**
 * main - main function for the shell
 * @argc: number of arguments passed to main
 * @argv: array of arguments passed to main
 * @environment: array of environment variables
 *
 * Return: 0 or exit status, or ?
 */

int main(int argc __attribute__((unused)), char **argv, char **environment)
{
	size_t len_buffer = 0;
	unsigned int is_pipe = 0, i;
	vars_t variabs = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	variabs.argv = argv;
	variabs.env = create_env(environment);
	signal(SIGINT, sig_handler);

	if (!isatty(STDIN_FILENO))
		is_pipe = 1;
	if (is_pipe == 0)
		_puts("$ ");
	sig_flag = 0;
	
	while (getline(&(variabs.buffer), &len_buffer, stdin) != -1)
	{
		sig_flag = 1;
		variabs.count++;
		variabs.commands = tokenize(variabs.buffer, ";");
		for (i = 0; variabs.commands && variabs.commands[i] != NULL; i++)
		{
			variabs.av = tokenize(variabs.commands[i], "\n \t\r");
			if (variabs.av && variabs.av[0])
				if (builtins_check(&variabs) == NULL)
					check_for_path(&variabs);
			free(variabs.av);
		}
		free(variabs.buffer);
		free(variabs.commands);
		sig_flag = 0;
		if (is_pipe == 0)
			_puts("$ ");
		variabs.buffer = NULL;
	}

	if (is_pipe == 0)
		_puts("\n");
	free_env(variabs.env);
	
	free(variabs.buffer);
	
	exit(variabs.status);
}
