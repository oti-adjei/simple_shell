#include "shell.h"

/**
 * _puts - writes a string to standard output
 * @str: string to write
 *
 * Return: number of chars printed or -1 on failure
 */


ssize_t _puts(char *str)
{
	ssize_t num, len;

	num = _strlen(str);
	len = write(STDOUT_FILENO, str, num);
	if (len != num)
	{
		perror("Fatal Error");
		return (-1);
	}
	return (len);
}

/**
 * _strdup - returns pointer to new mem alloc space which contains copy
 * @strtodup: string to be duplicated
 *
 * Return: a pointer to the new duplicated string
 */

char *_strdup(char *strtodup)
{
	char *copy;

	int len, i;

	if (strtodup == 0)
		return (NULL);

	for (len = 0; strtodup[len]; len++)
		;
	copy = malloc((len + 1) * sizeof(char));

	for (i = 0; i <= len; i++)
		copy[i] = strtodup[i];

	return (copy);
}

/**
 * _stringcomp - compares two strings
 * @stringcomp1: first string, of two, to be compared in length
 * @stringcomp2: second string, of two, to be compared
 * Return: 0 on success, anything else is a failure
 */


int _stringcomp(char *stringcomp1, char *stringcomp2)
{
	int i;

	i = 0;

	while (stringcomp1[i] == stringcomp2[i])
	{
		if (stringcomp1[i] == '\0')
			return (0);
		i++;
	}

	return (stringcomp1[i] - stringcomp2[i]);
}

/*
 * _strcat - concatenates two strings
 * @strc1: the first string
 * @strc2: the second string
 *
 * Return: pointer
 */

char *_strcat(char *strc1, char *strc2)
{
	char *newstring;
	unsigned int length1, length2, newlen, i, j;

	length1 = 0;
	length2 = 0;
	if (strc1 == NULL)
		length1 = 0;
	else
	{
		for (length1 = 0; strc1[length1]; length1++)
			;
	}
	if (strc2 == NULL)
		length2 = 0;
	else
	{
		for (length2 = 0; strc2[length2]; length2++)
			;
	}
	newlen = length1 + length2 + 2;
	newstring = malloc(newlen * sizeof(char));
	if (newstring == NULL)
		return (NULL);
	for (i = 0; i < length1; i++)
		newstring[i] = strc1[i];
	newstring[i] = '/';
	for (j = 0; j < length2; j++)
		newstring[i + 1 + j] = strc2[j];
	newstring[length1 + length2 + 1] = '\0';
	return (newstring);
}

/*
 * _strlen - it returns the length of a string
 * @str: the string to be measured
 *
 * Return: length of string
 */


unsigned int _strlen(char *str)
{
	unsigned int length;


	length = 0;

	for (length = 0; str[length]; length++)
		;
	return (length);
}
