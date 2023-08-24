#include "shell.h"

/**
 * print_err - prints error msgs to standard error
 * @variabs: pointer to structure of variables
 * @msg: message to print out
 *
 * Return: void
 */
void print_err(vars_t *variabs, char *msg)
{
	char *count;

	_putserr(variabs->argv[0]);
	_putserr(": ");

	count = _uitoa(variabs->count);
	_putserr(count);
	free(count);

	_putserr(": ");
	_putserr(variabs->av[0]);
	if (msg){
		_putserr(msg);
	}
	else
		perror("");
}

/**
 * _putserr - prints string to standard error
 * @str: string to print
 * Return: void
 */
void _putserr(char *str)
{
	ssize_t num, length;

	num = _strlen(str);
	length = write(STDERR_FILENO, str, num);
	
	if (length != num)
	{
		perror("Fatal Error");
		exit(1);
	}

}

/**
 * _uitoa - converts  unsigned int to a string
 * @counter: an unsigned int to convert
 * Return: pointer to converted string
 */

char *_uitoa(unsigned int counter)
{
	char *numbstr;
	unsigned int tempp, digits;

	tempp = counter;
	for (digits = 0; tempp != 0; digits++)
		tempp /= 10;
	numbstr = malloc(sizeof(char) * (digits + 1));
	
	if (numbstr == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	numbstr[digits] = '\0';

	for (--digits; counter; --digits)
	{
		numbstr[digits] = (counter % 10) + '0';
		counter /= 10;
	}
	return (numbstr);
}
