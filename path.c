#include "shell.h"

/*
 * path_exec - executes a command in the path
 * @commandp: full path to the command
 *
 * @variabs: pointer to struct of variables
 *
 * Return: 0 on success, 1 on failure
 */


int path_exec(char *commandp, vars_t *variabs)
{
	pid_t child_pidd;

	if (access(commandp, X_OK) == 0)
	{
		child_pidd = fork();
		if (child_pidd == -1)
			print_err(variabs, NULL);
		if (child_pidd == 0)
		{
			if (execve(commandp, variabs->av, variabs->env) == -1)
				print_err(variabs, NULL);
		}
		else
		{
			wait(&variabs->status);
		
			if (WIFEXITED(variabs->status))
				variabs->status = WEXITSTATUS(variabs->status);
			else if (WIFSIGNALED(variabs->status) && WTERMSIG(variabs->status) == SIGINT)
				variabs->status = 130;
			return (0);
		}

		variabs->status = 127;
		return (1);
	}
	else

	{
		print_err(variabs, ": Permission denied\n");
		variabs->status = 126;
	}
	return (0);
}

/*
 * find_path - finds the PATH variable
 * @env_var: array of environment variables
 *
 * Return: pointer to the node that contains the PATH, or NULL on failure
 */


char *find_path(char **env_var)
{
	char *path = "PATH=";
	unsigned int indexpos, j;

	for (indexpos = 0; env_var[indexpos] != NULL; indexpos++)
	{
		for (j = 0; j < 5; j++)

			if (path[j] != env_var[indexpos][j])
				break;
		if (j == 5)
			break;
	}
	return (env_var[indexpos]);
}


/*
 * check_for_path - checks if command is in the PATH
 * @variabs: variables
 *
 * Return: void
 */


void check_for_path(vars_t *variabs)
{
	char *path, *path_dup = NULL, *check = NULL;
	unsigned int i = 0, r = 0;
	char **path_tokens;
	struct stat buf;

	if (dir_chec(variabs->av[0]))
		r = execute_cwd(variabs);
	else
	{
		path = find_path(variabs->env);
		if (path != NULL)
		{
			path_dup = _strdup(path + 5);
			path_tokens = tokenize(path_dup, ":");
			for (i = 0; path_tokens && path_tokens[i]; i++, free(check))
			{
				check = _strcat(path_tokens[i], variabs->av[0]);
				if (stat(check, &buf) == 0)
				{
					r = path_exec(check, variabs);
					free(check);
					break;
				}
			}
			free(path_dup);
			if (path_tokens == NULL)
			{
				variabs->status = 127;
				new_exit(variabs);
			}
		}
		if (path == NULL || path_tokens[i] == NULL)
		{
			print_err(variabs, ": not found\n");
			variabs->status = 127;
		}
		free(path_tokens);
	}
	if (r == 1)
		new_exit(variabs);
}
/*
 * execute_cwd - executes the command in the current working directory
 * @variabs: pointer to struct of variables
 * Return: 0 on success, 1 on failure
 */

int execute_cwd(vars_t *variabs)
{
	pid_t child_pidd;
	struct stat bufs;

	if (stat(variabs->av[0], &bufs) == 0)
	{
		if (access(variabs->av[0], X_OK) == 0)
		{
			child_pidd = fork();
			if (child_pidd == -1)
				print_err(variabs, NULL);
			if (child_pidd == 0)
			{
				if (execve(variabs->av[0], variabs->av, variabs->env) == -1)
					print_err(variabs, NULL);
			}
			else
			{
				wait(&variabs->status);
				if (WIFEXITED(variabs->status))
					variabs->status = WEXITSTATUS(variabs->status);
				else if (WIFSIGNALED(variabs->status) && WTERMSIG(variabs->status) == SIGINT)
					variabs->status = 130;

				return (0);
			}
			variabs->status = 127;
			return (1);
		}
		else
		{
			print_err(variabs, ": Permission denied\n");
			variabs->status = 126;
		}
		return (0);
	}
	print_err(variabs, ": not found\n");
	variabs->status = 127;
	
	return (0);
}

/*
 * dir_chec - checks if command is a part of a path
 * @str: command
 *
 * Return: 1 on success, 0 on failure
 */
int dir_chec(char *str)
{
	unsigned int indexpos;

	for (indexpos = 0; str[indexpos]; indexpos++)
	{
		if (str[indexpos] == '/')
			return (1);
	}

	return (0);
}
