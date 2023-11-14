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
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
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
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
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


/* Function prototypes from toem_shell_loop.c */
void fork_cmd(info_t *info);
void find_cmd(info_t *info);
int seek_builtin(info_t *info);
int shell_cycle(info_t *info, char **av);

/* Function prototypes from toem_parser.c */
int check_for_command(info_t *info, char *path);
char *copy_characters(char *pathstr, int start, int stop);
char *seek_cmd_path(info_t *info, char *pathstr, char *cmd);

/* loophsh.c */
int loophsh(char **);

/* Function prototypes from toem_errors.c */
int write_to_file_descriptor(char c, int fd);
int print_string_to_fd(char *str, int fd);
int print_error_character(char c);
void print_error_string(char *str);

/* Function prototypes from toem_string.c */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);

/* Function prototypes from toem_string1.c */
char *replicate_string(char *dest, char *src);
char *generate_duplicate(const char *str);
void echo_string(char *str);
int buffered_char_output(char c);

/* Function prototypes from toem_exits.c */
char *copy_partial_string(char *dest, char *src, int n);
char *append_limited_chars(char *dest, char *src, int n);
char *find_char(char *s, char c);

/* Function prototypes from toem_tokenizer.c */
char **divide_string(char *str, char d);
char **segment_string(char *str, char *d);

/* Function prototypes from toem_realloc.c */
char *fill_memory(char *s, char b, unsigned int n);
void array_free(char **pp);
void *resize_memory(void *ptr, unsigned int old_size, unsigned int new_size);


/* Function prototype from toem_memory.c */
int bfree(void **ptr);

/* Function prototypes from toem_atoi.c */
int _atoi(char *s);
int _isalpha(int c);
int is_delim(char c, char *delim);
int interactive(info_t *info);

/* Function prototypes from toem_errors1.c */
void remove_comments(char *buf);
char *convert_number(long int num, int base, int flags);
int print_d(int input, int fd);
void print_error(info_t *info, char *error_msg);
int _erratoi(char *s);

/* Function prototypes from toem_builtin.c */
int help_command(info_t *info);
int change_directory(info_t *info);
int exit_shell(info_t *info);

/* Function prototypes from toem_builtin1.c */
int display_history(info_t *info);
int remove_alias(info_t *info, char *str);
int create_or_update_alias(info_t *info, char *str);
int output_alias(list_t *node);
int manage_alias(info_t *info);

/* Function prototypes from toem_getLine.c */
void sigintHandler(int sig_num);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);

/* Function prototypes from toem_getinfo.c */
void release_info_resources(info_t *info, int all);
void establish_info(info_t *info, char **av);
void reset_info(info_t *info);

/* Function prototypes from toem_environ.c */
int construct_env_list(info_t *info);
char *retrieve_env_value(info_t *info, const char *name);
int environment_variable_set(info_t *info);
int environment_variable_unset(info_t *info);
int display_environment(info_t *info);

/* Function prototypes from toem_getenv.c */
int modify_environment(info_t *info, char *var, char *value);
int discard_environment_variable(info_t *info, char *var);
char **fetch_environment_snapshot(info_t *info);

/* Function prototypes from toem_history.c */
int store_history(info_t *info);
char *locate_history_file(info_t *info);
int load_history(info_t *info);
int update_history_numbers(info_t *info);
int insert_history_entry(info_t *info, char *buf, int linecount);

/* Function prototypes from toem_list.c */
void clear_list(list_t **head_ptr);
int remove_node_by_index(list_t **head, unsigned int index);
size_t display_list_strings(const list_t *h);
list_t *append_node_to_end(list_t **head, const char *str, int num);
list_t *prepend_node(list_t **head, const char *str, int num);

/* Function prototypes from toem_list1.c */
ssize_t retrieve_node_index(list_t *head, list_t *node);
list_t *find_node_prefix(list_t *node, char *prefix, char c);
size_t echo_list(const list_t *h);
char **list_to_array(list_t *head);
size_t count_list(const list_t *h);

/* Function prototypes from toem_vars.c */
int swap_string(char **old, char *new);
int insert_variables(info_t *info);
int swap_aliases(info_t *info);
void verify_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int detect_chain(info_t *info, char *buf, size_t *p);

#endif
