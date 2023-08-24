#include "shell.h"

/**
 * builtins_check - checks if the command is a builtin
 * @variabs: the  variables
 * Return: pointer to the function or NULL
 */

void (*builtins_check(vars_t *variabs))(vars_t *variabs)
{
	unsigned int indexpos;
	builtins_t checker[] = {
		{"exit", new_exit},
		{"env", _environ},
		{"setenv", fresh_env},
		{"unsetenv", new_unsetenv},
		{NULL, NULL}
	};

	for (indexpos = 0; checker[indexpos].f != NULL; indexpos++)
	{
		if (_stringcomp(variabs->av[0], checker[indexpos].name) == 0)
			break;
	}
	if (checker[indexpos].f != NULL)
		checker[indexpos].f(variabs);
	return (checker[indexpos].f);
}

 /* _environ - shows the current environment
 * @variabss: structure of variables
 *
 * Return: void.
 */
void _environ(vars_t *variabs)
{
	unsigned int indexpos;

	for (indexpos = 0; variabs->env[indexpos]; indexpos++)
	{
		_puts(variabs->env[indexpos]);
		_puts("\n");
	}
	variabs->status = 0;
}

/**
 * new_exit - exit program
 * @variabss:the  variables
 *
 * Return: void
 */
void new_exit(vars_t *variabs)
{
	int status;

	if (_stringcomp(variabs->av[0], "exit") == 0 && variabs->av[1] != NULL)
	{
		status = _atoi(variabs->av[1]);

		if (status == -1)
		{
			variabs->status = 2;
			print_err(variabs, ": Illegal number: ");
			_putserr(variabs->av[1]);
			_putserr("\n");
			free(variabs->commands);
			variabs->commands = NULL;
			return;
		}
		variabs->status = status;
	}
	free(variabs->buffer);
	free(variabs->av);

	free(variabs->commands);
	free_env(variabs->env);

	exit(variabs->status);
}


/**
 * fresh_env - create a new environment variable, or edit an existing variable
 * @variabs: pointer to structure of variables
 * Return: void
 */
void fresh_env(vars_t *variabs)
{
	char **key;
	char *var;

	if (variabs->av[1] == NULL || variabs->av[2] == NULL)
	{
		print_err(variabs, ": Incorrect number of arguments\n");
		variabs->status = 2;
		return;
	}
	key = key_find(variabs->env, variabs->av[1]);

	if (key == NULL)
		key_add(variabs);
	else
	{
		var = add_value(variabs->av[1], variabs->av[2]);
		if (var == NULL)
		{
			print_err(variabs, NULL);
			free(variabs->buffer);
			free(variabs->commands);

			free(variabs->av);
			free_env(variabs->env);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	variabs->status = 0;
}

/**
 * new_unsetenv - remove an environment variable
 * @variabs: pointer to a struct of variables
 * Return: void
 */
void new_unsetenv(vars_t *variabs)
{
	char **key, **newenv;
	unsigned int indexpos, j;

	if (variabs->av[1] == NULL)
	{
		print_err(variabs, ": Incorrect number of arguments\n");
		variabs->status = 2;
		return;
	}
	key = key_find(variabs->env, variabs->av[1]);

	if (key == NULL)
	{
		print_err(variabs, ": No variable to unset");
		return;
	}

	for (indexpos = 0; variabs->env[indexpos] != NULL; indexpos++)
		;
	newenv = malloc(sizeof(char *) * indexpos);
	if (newenv == NULL)
	{
		print_err(variabs, NULL);
		variabs->status = 127;
		new_exit(variabs);
	}

	for (indexpos = 0; variabs->env[indexpos] != *key; indexpos++)
		newenv[indexpos] = variabs->env[indexpos];

	for (j = indexpos + 1; variabs->env[j] != NULL; j++, indexpos++)
		newenv[indexpos] = variabs->env[j];
	newenv[indexpos] = NULL;
	free(*key);

	free(variabs->env);
	variabs->env = newenv;
	variabs->status = 0;
}
