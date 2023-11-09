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

/* Buffer sizes for reading and writing operations */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Command execution status codes */
#define CMD_NORM  0
#define CMD_OR    1
#define CMD_AND   2
#define CMD_CHAIN 3

/* Flags for number conversion */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED  2

/* Configuration flags */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* History feature constants */
#define HIST_FILE  ".simple_shell_history"
#define HIST_MAX   4096

/* Environment variables global reference */
extern char **environ;

/* Linked list structure for various shell data */
typedef struct liststr
{
    int num;                  /* Index number in the list */
    char *str;                /* String data */
    struct liststr *next;     /* Pointer to the next node */
} list_t;

/* Main shell information structure */
typedef struct passinfo
{
    char *arg;                /* Raw command line string */
    char **argv;              /* Tokenized command arguments */
    char *path;               /* Command path */
    int argc;                 /* Argument count */
    unsigned int line_count;  /* Line count for input */
    int err_num;              /* Error code for exits */
    int linecount_flag;       /* Flag to count current line */
    char *fname;              /* Filename of the shell program */
    list_t *env;              /* Environment variables list */
    list_t *history;          /* Command history list */
    list_t *alias;            /* Aliases list */
    char **environ;           /* Custom environment array */
    int env_changed;          /* Flag for environment change */
    int status;               /* Last command exit status */

    char **cmd_buf;           /* Buffer for command chaining */
    int cmd_buf_type;         /* Type of command chain */
    int readfd;               /* File descriptor for reading */
    int histcount;            /* History line count */
} info_t;

/* Macro to initialize the info structure with default values */
#define INFO_INIT {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}

/* Struct for builtin commands */
typedef struct builtin
{
    char *type;               /* Builtin command name */
    int (*func)(info_t *);    /* Function to execute the builtin */
} builtin_table;

/* Function prototypes grouped by functionality */

/* Primary shell loop functions */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* Command parsing functions */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* Error handling functions */
void _eputs(char *);
int _eputchar(char);
int _putfd(char, int);
int _putsfd(char *, int);

/* String manipulation functions */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* More string manipulation functions */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* String functions related to command execution */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* Tokenization functions */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* Memory reallocation functions */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* Memory management functions */
int bfree(void **);

/* Character and string conversion functions */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* Error and exit handling functions */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* Builtin commands functions */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* Additional builtin commands functions */
int _myhistory(info_t *);
int _myalias(info_t *);

/* Input line acquisition functions */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* Shell state initialization and cleanup functions */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* Environment variables handling functions */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* Environment variables acquisition functions */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* History management functions */
char *get_history_file(info_t *);
int write_history(info_t *);
int read_history(info_t *);
int build_history_list(info_t *, char *, int);
int renumber_history(info_t *);

/* Linked list handling functions */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* More linked list functions */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* Command execution utility functions */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif /* _SHELL_H_ */
