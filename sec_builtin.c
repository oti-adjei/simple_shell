#include "shell.h"

/**
 * key_add - create a new environment variable
 * @variabs: pointer to struct of variables
 *
 * Return: void
 */

void key_add(vars_t  *variabs)
{
	unsigned int indexpos;
	char **newenv_var;

	for (indexpos = 0; variabs->env[indexpos] != NULL; indexpos++)
		;
	newenv_var = malloc(sizeof(char *) * (indexpos + 2));
	if (newenv_var == NULL)
	{
		print_err(variabs, NULL);
		variabs->status = 127;
		new_exit(variabs);
	}
	for (indexpos = 0; variabs->env[indexpos] != NULL; indexpos++)
		newenv_var[indexpos] = variabs->env[indexpos];
	newenv_var[indexpos] = add_value(variabs->av[1], variabs->av[2]);

	if (newenv_var[indexpos] == NULL)
	{
		print_err(variabs, NULL);
		free(variabs->buffer);

		free(variabs->commands);
		free(variabs->av);

		free_env(variabs->env);
		free(newenv_var);
		exit(127);
	}
	newenv_var[indexpos + 1] = NULL;
	free(variabs->env);
	variabs->env = newenv_var;
}

/**
 * key_find - finds an env variable
 * @env_var: array of env variables
 * @key: environment variable to find
 *
 * Return: pointer to address of the env variable
 */

char **key_find(char **env_var, char *key)
{
	unsigned int indexpos, j, len;

	len = _strlen(key);
	for (indexpos = 0; env_var[indexpos] != NULL; indexpos++)
	{
		for (j = 0; j < len; j++)
			if (key[j] != env_var[indexpos][j])
				break;
		if (j == len && env_var[indexpos][j] == '=')
			return (&env_var[indexpos]);
	}
	return (NULL);
}

/**
 * add_value - create a new environment variable string
 * @var_name: variable name
 * @var_value: variable value
 *
 * Return: pointer to the new string;
 */

char *add_value(char *var_name, char *var_value)
{
	unsigned int len_key, len_value, indexpos, j;
	char *new;

	len_key = _strlen(var_name);
	len_value = _strlen(var_value);

	new = malloc(sizeof(char) * (len_key + len_value + 2));
	if (new == NULL)
		return (NULL);
	for (indexpos = 0; var_name[indexpos] != '\0'; indexpos++)
		new[indexpos] = var_name[indexpos];
	new[indexpos] = '=';
	for (j = 0; var_value[j] != '\0'; j++)
		new[indexpos + 1 + j] = var_value[j];
	new[indexpos + 1 + j] = '\0';
	return (new);
}

/**
 * _atoi - converts  string into an integer
 * @strng: string to convert
 * Return: the integer value, or -1 if an error occurs
 */

int _atoi(char *strng)
{
	unsigned int indexpos, digits;
	int num = 0, num_max;

	num_max = INT_MAX;
	for (digits = 0; num_max != 0; digits++)
		num_max /= 10;

	for (indexpos = 0; strng[indexpos] != '\0' && indexpos < digits; indexpos++)
	{
		num *= 10;
		if (strng[indexpos] < '0' || strng[indexpos] > '9')
			return (-1);
		if ((indexpos == digits - 1) && (strng[indexpos] - '0' > INT_MAX % 10))
			return (-1);
		num += strng[indexpos] - '0';
		if ((indexpos == digits - 2) && (strng[indexpos + 1] != '\0') && (num > INT_MAX / 10))
			return (-1);
	}
	if (indexpos > digits)
		return (-1);
	return (num);
}
