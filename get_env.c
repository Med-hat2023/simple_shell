#include "shell.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * all_env - function to get all env
 * @env: environment
 * Return: None
 */
void all_env(char **env)
{
    size_t i;
	if (env == NULL)
		return;

	for (i = 0; env[i] != NULL; i++)
	{
		printf("%s\n", env[i]);
	}
}

/**
 * _getenv - Get the value of an environment variable
 * @name: Name of the environment variable we are getting the value for
 * Return: Pointer to the value of the environment variable or NULL(not found)
 */

char *_getenv(const char *name){
    size_t name_len;
    char **env;

    if(name == NULL || name[0] == '\0')
        return NULL;

    name_len = len_str(name);

    for(env = environ; *env != NULL; env++)
    {
        if(_strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '='){
            return (*env + name_len + 1);
        }
    }

    return (NULL);
}
/**
 * _setenv: function to set the value of the environment
 * @args: the arguments 
 */
int _setenv(char **args){
    if(args[1] == NULL || args[2] == NULL){
        _putserr("Usage:setenv VARIABLE VALUE\n");
        return (-1);
    }

    if(setenv(args[1], args[2], 1) != 0){
        perror("setenv");
        return (-1);
    }

    return (0);
}

/**
 * _unsetenv: function to unset the environment value
 * @args: the arguments
 *
 * Return: (0) it returns nothing
 */
int _unsetenv(char **args){
    if(args[1] == NULL){
        _putserr("Usage: unsetenv VARIABLE\n");
        return (-1);
    }

    if(unsetenv(args[1]) != 0){
        perror("unsetenv");
        return (-1);
    }
    return (0);
}
