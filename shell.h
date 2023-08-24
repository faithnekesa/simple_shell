#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>

#define USE_STRTOK 0
#define USE_GETLINE 0
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr -The list for singly linked list
 * @num:The number field
 * @str:String struct
 * @next:A pointer to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo -A struct that has pseudo arguments
 * to pass into a function,
 *@arg:output string arguments from getLine
 *@argv:Argument array
 *@path:String path for current command
 *@argc:Argument count
 *@line_count: Error count
 *@err_num:Error code for exit
 *@linecount_flag: if on count this line of input
 *@fname:Program filename
 *@env: linked list local copy of environ
 *@environ: Modified copy of the environ
 *@history:History node
 *@alias:The alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin -Function that contains a builtin string &
 *related function
 *@type:Builtin command flag
 *@func:The struct function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int hsh(info_t *, char **);
void find_cmd(info_t *);
int find_builtin(info_t *);
int loophsh(char **);
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
void fork_cmd(info_t *);
int myStrlen(char *);
int myStrcmp(char *, char *);
char *startsWith(const char *, const char *);
char *find_path(info_t *, char *, char *);
void myEputs(char *);
int myPutfd(char c, int fd);
char *myStrdup(const char *);
int myPutsfd(char *str, int fd);
int myPutchar(char);
int myPutchar(char);
char *myStrncpy(char *, char *, int);
char *myStrcat(char *, char *);
char *myStrcpy(char *, char *);
void myPuts(char *);
char **strtow(char *, char *);
char *myStrchr(char *, char);
char *myStrncat(char *, char *, int);
char *myMemset(char *, char, unsigned int);
void *myRealloc(void *, unsigned int, unsigned int);
char **strtow2(char *, char);
void ffree(char **);
char **strtow2(char *, char);
int isDelim(char, char *);
int bfree(void **);
int myAtoi(char *);
int isAlpha(int);
int interactive(info_t *);
void remove_comments(char *);
void print_error(info_t *, char *);
int myExit(info_t *);
int print_d(int, int);
char *convert_number(long int, int, int);
int myErratoi(char *);
int myHistory(info_t *);
int myCd(info_t *);
int myAlias(info_t *);
int myHelp(info_t *);
void sigintHandler(int);
int myGetline(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
void clear_info(info_t *);
int mysetEnv(info_t *);
int populate_env_list(info_t *);
char *getEnv(info_t *, const char *);
int myEputchar(char c);
int myEnv(info_t *);
int myunsetEnv(info_t *);
int setEnv(info_t *, char *, char *);
int unsetEnv(info_t *, char *);
char **get_environ(info_t *);
int write_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int read_history(info_t *info);
char *get_history_file(info_t *info);
int renumber_history(info_t *info);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
list_t *add_node(list_t **, const char *, int);
void free_list(list_t **);
int delete_node_at_index(list_t **, unsigned int);
size_t print_list(const list_t *);
size_t list_len(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
char **list_to_strings(list_t *);
int is_chain(info_t *, char *, size_t *);
int replace_string(char **, char *);
int replace_vars(info_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
ssize_t get_node_index(list_t *, list_t *);

#endif
