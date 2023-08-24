#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>


/**
 * struct variables - variables
 * @av: command line arguments
 * @buffer: buffer of command
 * @env: environment variables
 * @count: count of commands entered
 * @argv: arguments at opening of shell
 * @status: exit status
 * @commands: double pointer to commands
 */
typedef struct variables
{
	char **av;
	char *buffer;
	char **env;
	size_t count;
	char **argv;
	int status;
	char **commands;
} vars_t;

/**
 * struct builtins - struct for the builtin functions
 * @name: name of builtin command
 * @f: function for corresponding builtin
 */
typedef struct builtins
{
	char *name;
	void (*f)(vars_t *);
} builtins_t;

char **create_env(char **env);
void free_env(char **env);

ssize_t _puts(char *str);
char *_strdup(char *strtodup);
int _stringcomp(char *stringcomp1, char *stringcomp2);
char *_strcat(char *strc1, char *strc2);
unsigned int _strlen(char *str);

char **tokenize(char *bufer, char *delimiter);
char **_re_alloc(char **old_ptr, size_t *size);
char *new_strngtok(char *strng, const char *delim);

void (*builtins_check(vars_t *variabs))(vars_t *variabs);
void new_exit(vars_t *variabs);
void _environ(vars_t *variabs);

void fresh_env(vars_t *variabs);
void new_unsetenv(vars_t *variabs);

void key_add(vars_t *variabs);
char **key_find(char **env_var, char *key);
char *add_value(char *key, char *value);
int _atoi(char *str);

void check_for_path(vars_t *variabs);
int path_exec(char *commandp, vars_t *variabs);
char *find_path(char **env);
int execute_cwd(vars_t *variabs);
int dir_chec(char *str);

void print_err(vars_t *variabs, char *msg);
void _putserr(char *str);
char *_uitoa(unsigned int counter);

#endif /* _SHELL_H_ */
