#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define ADJUSTABLE_WRITE_BUFFER_SIZE 1024
#define CLEAR_BUFFER  -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define lowercaseConversion     1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststring
{
	int num;
	char *string;
	struct liststring *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *argumentCount;
	char **argumentVector;
	char *directory;
	int argumentcount;
	unsigned int line_count;
	int exitErrorNumber;
	int linecount_flag;
	char *fileName;
	list_t *environmentVariables;
	list_t *commandList;
	list_t *alternateName;
	char **environ;
	int env_changed;
	int exitStatus;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void printText(char *text);
int writeToStderr(char outputChar);
int writeToDescriptor(char outputChar, int fileDescriptor);
int transmitStringToDescriptor(char *inputString, int fileDescriptor);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *CustomStringCopy(char *output, char *source, int limi);
char *ConcatenateLimited(char *destination, char *source, int limit);
char *FindCharacter(char *string, char character);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c ********************************/

int checkInteractiveMode(info_t *info);

int isDelimiter(char character, char *delimiter);

int isAlphabetic(int character);

int stringToIntConverter(char *inputString);

/* toem_errors1.c */

int convertStringToInt(char *inputString);
void displayErrorInfo(info_t *information, char *errorMessage);
int printDecimalToFD(int value, int fileDescriptor);
char *numberToString(long int number, int initialBase, int conversionFlags);
void deactivateHash(char *inputString);

/* toem_builtin.c */
int exitShell(info_t *cmdInfo);
int changeCurrentDirectory(info_t *shellInfo);
int displayShellHelp(info_t *commandInfo);

/* toem_builtin1.c */
int displayCommandLog(info_t *shellInfo);
int dissolve_alias_connection(info_t *data_info, char *target_sequence);
int associate_string_with_alias(info_t *data_info, char *target_sequence);
int display_entry(list_t *displayed_entry);
int execute_alias_operations(info_t *arguments_info);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void initializeInfo(info_t *data);
void configureInfo(info_t *data, char **arguments);
void free_info(info_t *, int);

/* toem_environ.c */

int displayEnvironment(info_t *context);

char *findEnvironmentValue(info_t *context, const char *varName);
int updateOrCreateEnvVariable(info_t *information);
int removeEnvironmentVariable(info_t *information);
int initializeEnvironmentList(info_t *inputInfo);

/* toem_getenv.c */
char **sync_and_get_environment(info_t *data);
int remove_environment_variable(info_t *data, char *variable);
int initialize_or_modify_environment_variable(info_t *data, char *variable, char *updated_value);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
