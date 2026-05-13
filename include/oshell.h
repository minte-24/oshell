#ifndef OSHELL_H

#define OSHELL_H



#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <ctype.h>
#define MAX_LINE 1024
#define MAX_ARGS 128
#define ERR_MSG "An error has occurred\n"

/* global */
extern int last_status;

/* ===== utils ===== */
void print_error(void);
char *expand(char *token);
char *trim_whitespace(char *str);

/* ===== path ===== */
void init_path(void);
void free_path(void);
void set_path(char **dirs);
char *find_cmd(char *cmd);

/* ===== alias ===== */
void alias_init(void);
void alias_destroy(void);
void alias_set(char *name, char *value);
char *alias_get(char *name);
void alias_print(char **args);

/* ===== builtins ===== */
int is_builtin(char *cmd);
int run_builtin(char **args);

/* ===== executor ===== */
int execute_single(char **args, char *redir);
int execute_parallel(char ***cmds, int count);

/* ===== parser ===== */
void execute_line(char *line);
#endif
