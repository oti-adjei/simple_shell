#include "shell.h"

/**
 * create_env - make the shell env from the environment pass to main
 * @env_var: env passed to main
 * Return: pointer to the new environment
 */

char **create_env(char **env_var)
{
	char **newenv_var = NULL;
	size_t i;

	for (i = 0; env_var[i] != NULL; i++);

	newenv_var = malloc(sizeof(char *) * (i + 1));

	if (newenv_var == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	for (i = 0; env_var[i] != NULL; i++)
		newenv_var[i] = _strdup(env_var[i]);
	newenv_var[i] = NULL;
	return (newenv_var);
}

/**
 * free_env - free the shell's env
 * @env_var: shell's env
 * Return: void
 */

void free_env(char **env_var)
{
	unsigned int indexpos;

	for (indexpos = 0; env_var[indexpos] != NULL; indexpos++)
		free(env_var[indexpos]);

	free(env_var);
}
