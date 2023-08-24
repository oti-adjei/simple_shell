#include "shell.h"

/**
 * _re_alloc - reallocates pointer to double the space
 * @old_ptr: pointer to old array
 *
 * @size: pointer to number of elements in old array
 * Return: pointer to the new array
 */

char **_re_alloc(char **old_ptr, size_t *size)
{
	char **new;
	size_t indexpos;

	new = malloc(sizeof(char *) * ((*size) + 10));
	if (new == NULL)
	{
		free(old_ptr);
		return (NULL);
	}

	for (indexpos = 0; indexpos < (*size); indexpos++)
	{
		new[indexpos] = old_ptr[indexpos];
	}

	*size += 10;
	free(old_ptr);
	return (new);
}
