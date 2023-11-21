#include "shell.h"
#include <stdbool.h>
#include <stdlib.h>
/**
 * execute_shell - main execution function with support for logical operators
 * @userInput: user input string
 * @env: environment
 * @av: arguments
 * Return: exit_status
 */
int execute_shell(char *userInput, char **env, char **av)
{
    int pathValue = 0, exit_status = 0, n = 0;
    char **user_command = NULL;
    bool andOperator = false, orOperator = false;
    int i;
    char **before_op, **after_op;

    user_command = split_command(userInput);
    if (!user_command)
        return (exit_status);

    /*Handle "exit" command*/
    if ((!_strcmp(user_command[0], "exit")) && user_command[1] == NULL)
    {
        exit_shell(user_command, userInput, exit_status);
        free(user_command);
        return (exit_status);
    }

    /*Handling "env" command*/
    if (!_strcmp(user_command[0], "env"))
    {
        all_env(env);
        free(user_command);
        return (exit_status);
    }
    /* handle the cd command*/
    if(!_strcmp(user_command[0], "cd"))
    {
        my_cd(user_command);
        free(user_command);
        return (exit_status);
    }
    /* Handle the alias command */
    if(!_strcmp(user_command[0], "alias")){
        my_alias(user_command);
        free(user_command);
        return (exit_status);
    }

    /*Handle logical operators*/
    for (i = 0; user_command[i] != NULL; i++)
    {
        if (!_strcmp(user_command[i], "&&")||!_strcmp(user_command[i], ";"))
        {
            andOperator = true;
            user_command[i] = NULL;
        }
        else if (!_strcmp(user_command[i], "||"))
        {
            orOperator = true;
            user_command[i] = NULL;
        }
    }

    /*Find the path and execute commands accordingly*/
    n = find_path(&user_command[0], env);

    /*Separate commands before and after logical operators*/
    before_op = user_command;
    after_op = NULL;

    if (andOperator || orOperator)
    {
        int index = n + 1;
        while (user_command[index] != NULL)
        {
            after_op = &user_command[index];
            index++;
        }
    }

    if (andOperator)
    {
        if (execute(before_op, av, env, userInput, pathValue, n) == 0)
        {
            exit_status = execute(after_op, av, env, userInput, pathValue, n);
        }
    }
    else if (orOperator)
    {
        if (execute(before_op, av, env, userInput, pathValue, n) != 0)
        {
            exit_status = execute(after_op, av, env, userInput, pathValue, n);
        }
    }
    else
    {
        exit_status = execute(user_command, av, env, userInput, pathValue, n);
    }

    if (n == 0)
        free(user_command[0]);

    free(user_command);
    return (exit_status);
}
