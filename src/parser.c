#include "../include/oshell.h"



static char **parse_args(char *cmd, char **redir) {

    char **args = malloc(sizeof(char *) * MAX_ARGS);

    int i = 0;



    *redir = NULL;



    char *token = strtok(cmd, " \t\n");

    while (token) {

        if (strcmp(token, ">") == 0) {

            token = strtok(NULL, " \t\n");

            if (!token || *redir) {

                print_error();

                free(args);

                return NULL;

            }

            *redir = strdup(token);

        } else {

            args[i++] = expand(token);

        }

        token = strtok(NULL, " \t\n");

    }

    args[i] = NULL;

    return args;

}



void execute_line(char *line) {

    char *comment = strchr(line, '#');

    if (comment) *comment = '\0';



    line = trim_whitespace(line);

    if (*line == '\0') return;



    char *saveptr;

    char *segment = strtok_r(line, ";", &saveptr);



    while (segment) {

        segment = trim_whitespace(segment);



        if (strstr(segment, "&&") || strstr(segment, "||")) {

            char *op = strstr(segment, "&&") ? "&&" : "||";

            char *left = strtok(segment, op);

            char *right = strtok(NULL, op);



            if (!left || !right) {

                print_error();

                return;

            }



            execute_line(left);



            if ((strcmp(op, "&&") == 0 && last_status == 0) ||

                (strcmp(op, "||") == 0 && last_status != 0))

                execute_line(right);



        } else if (strchr(segment, '&')) {

            char *cmds[MAX_ARGS];

            int count = 0;



            char *p = strtok(segment, "&");

            while (p) {

                cmds[count++] = strdup(trim_whitespace(p));

                p = strtok(NULL, "&");

            }



            char ***argvs = malloc(sizeof(char **) * count);

            char *redir = NULL;



            for (int i = 0; i < count; i++)

                argvs[i] = parse_args(cmds[i], &redir);



            last_status = execute_parallel(argvs, count);

        } else {

            char *redir = NULL;

            char **args = parse_args(segment, &redir);

            if (!args) return;



            last_status = execute_single(args, redir);

        }



        segment = strtok_r(NULL, ";", &saveptr);

    }

}
