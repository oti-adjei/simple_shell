#include "shell.h"


/**
 * tokenize - purpose to tokenize a buffer with a delimiter
 * @bufer: buffer meant to tokenize
 *
 * @delimiter: delimiter to tokenize alongside
 * Return: pointer to an array of pointers to the tokens
 */
char **tokenize(char *bufer, char *delimiter)
{
	char **tokens = NULL;
	size_t indexpos = 0, mcount = 10;

	if (bufer == NULL)
		return (NULL);
	
	tokens = malloc(sizeof(char *) * mcount);
	if (tokens == NULL)
	{
		perror("Fatal Error");
		return (NULL);
	}
	
	while ((tokens[indexpos] = new_strngtok(bufer, delimiter)) != NULL)
	{
		indexpos++;
		if (indexpos == mcount)
		{
			tokens = _re_alloc(tokens, &mcount);
			if (tokens == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		bufer = NULL;
	}
	return (tokens);
}
