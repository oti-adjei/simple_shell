#include "shell.h"

/**
 * chec_match - checks if a character matches any in a string
 * @cc: check character
 * @strng: string to check
 *
 * Return: 1 if match, 0 if not
 */

unsigned int chec_match(char cc, const char *strng)
{
	unsigned int indexpos;

	for (indexpos = 0; strng[indexpos] != '\0'; indexpos++)
	{
		if (cc == strng[indexpos])
			return (1);
	}
	return (0);
}

/**
 *
 * new_strngtok - custom strngtok
 * @strng: string to tokenize
 * @delim: delimiter to tokenize against
 *
 * Return: pointer to the next token or NULL
 */
char *new_strngtok(char *strng, const char *delim)
{
	static char *token_start;
	static char *next_token;
	unsigned int indexpos;

	if (strng != NULL)
		next_token = strng;
	token_start = next_token;
	if (token_start == NULL)
		return (NULL);
	for (indexpos = 0; next_token[indexpos] != '\0'; indexpos++)
	{
		if (chec_match(next_token[indexpos], delim) == 0)
			break;
	}

	if (next_token[indexpos] == '\0' || next_token[indexpos] == '#')
	{
		next_token = NULL;
		return (NULL);
	}
	token_start = next_token + indexpos;
	next_token = token_start;
	for (indexpos = 0; next_token[indexpos] != '\0'; indexpos++)
	{
		if (chec_match(next_token[indexpos], delim) == 1)
			break;
	}

	if (next_token[indexpos] == '\0')
		next_token = NULL;
	else
	{
		next_token[indexpos] = '\0';
		next_token = next_token + indexpos + 1;
		
		if (*next_token == '\0')
			next_token = NULL;
	}
	return (token_start);
}
