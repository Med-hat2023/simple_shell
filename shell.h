#ifndef SHELL_H
#define SHELL_H
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <stddef.h> /* for the size_t part mainly*/

/* aias stuff */
#define MAX_ALIASES 100
#define MAX_ALIAS_NAME 50
#define MAX_ALIAS_VALUE 100

extern char **environ;

int _strcmp(const char *s1, const char *s2);
size_t _strncmp(const char *s1, const char *s2, size_t n);
int len_str(const char *);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _putchar(char c);
char *extract_path(char **env);
int find_path(char **arg, char **env);
char *user_input(void);
void all_env(char **env);
char **split_command(char *lineptr);
void exit_shell(char **args, char *lineptr, int _exit);
int execute(char **arg, char **av, char **env, char *lineptr, int np, int c);
int stringToInt(const char *str);
char *extract_path(char **env);
char *new_strtok(char *str, const char *delim);
int find_char_index(const char *str, char c);
ssize_t my_getline(char **lineptr, size_t *n);
void *my_realloc(void *ptr, unsigned int new_size);
int execute_shell(char *userInput, char **env, char **av);
void run_shell(char **env, char **av);
void my_cd(char **args);
char *_getenv(const char *name);
void _puts(char *str);
void _putserr(char *error);
int _setenv(char **args);
int _unsetenv(char **args);
void my_alias(char **args);
#endif /* SHELL_H */
