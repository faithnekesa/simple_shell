#ifndef SHELL_H
#define SHELL_H

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

/*buffers for read/write/flush*/
#define BUF_SIZE_READER 1024
#define BUF_SIZE_WRITER 1024
#define BUFFER_FLUSH -1
#define _CONVERT_LOWERCASE	1
#define _CONVERT_UNSIGNED	2
#define SYSTEM_GETLINE 0
#define SYSTEM_STRTOK 0
#define _CMD_NORM	0
#define _CMD_OR		1
#define _CMD_AND	2
#define _CMD_CHAIN	3
#define _HISTORY_FILE	".simple_shell_history"
#define _HISTORY_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	char *str;
	int num;

	struct liststr *next;
} list_t;

/**
 * struct passArgs -A struct that has pseudo arguments
 * to pass into a function,
 * @arg:output string arguments from getLine
 * @argc:Argument count
 * @argv:Argument array
 * @path:String path for the current command
 * @env: linked list local copy of environ
 * @lineCount: the error count
 * @alias: the alias node
 * @errorCode:The exit error code
 * @environ: custom modified copy of environ from LL env
 * @lineCountFlag: if on count this line of input
 * @fileName: the program filename
 * @cmdBuffer: address of pointer to cmdBuffer
 * @history: the history node
 * @envChanged: on if environ was changed
 * @historyLineCount: the history line number count
 * @commandStatus: the return commandStatus of the last exec'd command
 * @readFileDesc: the fileDesc from which to read line input
 * @cmdBufferType: CMD_type ||, &&, ;
 */
typedef struct passArgs
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int lineCount;
	int errorCode;
	int lineCountFlag;
	char *fileName;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int envChanged;
	int commandStatus;
	char **cmdBuffer;
	int cmdBufferType;
	int readFileDesc;
	int historyLineCount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}
/**
 * struct builtin -A struct which contains builtin
 * string and related functions
 * @type:Builtin command flag
 * @func:Builtin associated function
 */
typedef struct  builtin
{
	char *type;
	int (*func)(info_t *);
}  builtin_table;

char *_strcpy(char *dest, char *src);
int is_alpha(int c);
int is_delim(char c, char *delim);
int _atoi(char *s);
int myExit(info_t *);
int myHelp(info_t *);
int myChangeDir(info_t *);
char *convert_number(long int num, int base, int flags);
void myPuts(char *);
void printError(info_t *, char *);
int myPutchar(char);
void putsError(char *);
int putFileDesc(char inputChar, int fileDesc);
int myPutsfileDesc(char *str, int fileDesc);
/*int putFileDesc(char c, int fileDesc);*/
int putcharError(char);
/*int myPutsfileDesc(char *str, int fileDesc);*/
char *mygetEnv(info_t *, const char *);
int myEnv(info_t *);
int myHistory(info_t *info);
int myAlias(info_t *);
int mySetEnv(info_t *);
int myUnsetEnv(info_t *);
int unsetAlias(info_t *info, char *str);
int printAlias(list_t *node);
int createEnvList(info_t *);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
void setInfo(info_t *, char **);
void clearInfo(info_t *);
void freeInfo(info_t *, int);
char *_strchr(char *s, char c);
char *_strncpy(char *dest, char *src, int n);
int interactiveShell(info_t *info);
char *_strncat(char *dest, char *src, int n);
int _mydel_env(info_t *info, char *envar);
int _myset_env(info_t *info, char *envar, char *envalue);
char **get_environ(info_t *info);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
size_t _strlen(char *str);
int atoiError(char *);
char **myStrtok(char *str, char *d);
int printDecimal(int input, int fileDesc);
char *begin_with(const char *haystack, const char *needle);
list_t *add_node(list_t **head, const char *str, int index);
list_t *add_node_end(list_t **head, const char *str, int index);
size_t printList(const list_t *h);
char *findPath(info_t *, char *, char *);
char **list_elements(list_t *head);
size_t list_t_len(const list_t *h);
void free_list(list_t **head);
size_t printListStr(const list_t *h);
char *_strdup(const char *str);
int _putchar(char c);
void _puts(char *str);
ssize_t node_index(list_t *head, list_t *node);
list_t *node_prefix(list_t *node, char *prefix, char c);
int delete_node(list_t **head, unsigned int index);
void fork_cmd(info_t *info);
void find_pcmd(info_t *info);
int find_bcmd(info_t *info);
int is_cmd(info_t *, char *);
char *duplicateChars(char *, int, int);
char *findPath(info_t *, char *, char *);
int h_shell(info_t *info, char **av);
void check_chain(info_t *info, char *s, size_t *ptr, size_t index, size_t len);
int isChain(info_t *info, char *s, size_t *ptr);
int changeAlias(info_t *info);
int changeString(char **p, char *str);
int changeVars(info_t *info);
void *_realloc(void *p, unsigned int size1, unsigned int size2);
void s_free(char **p);
int p_free(void **p);
char *_memset(char *s, char size, unsigned int n);
int my_getline(info_t *info, char **ptr, size_t *length);
void signal_check(__attribute__((unused))int n);
ssize_t print_buf(info_t *info, char *buf, size_t *n);
ssize_t get_lineonly(info_t *info);
ssize_t input_buffer(info_t *info, char **buf, size_t *length);
void clearComments(char *buf);
int writeHistory(info_t *info);
int readHistory(info_t *info);
int createHistoryList(info_t *info, char *buf, int lc);
int renumberHistory(info_t *info);
char *getHistory(info_t *info);


#endif
