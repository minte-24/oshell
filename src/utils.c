#include "../include/oshell.h"



int last_status = 0;



void print_error(void) {

    write(STDERR_FILENO, ERR_MSG, strlen(ERR_MSG));

}



char *trim_whitespace(char *str) {

    while (isspace(*str)) str++;

    if (*str == 0) return str;



    char *end = str + strlen(str) - 1;

    while (end > str && isspace(*end)) end--;

    end[1] = '\0';

    return str;

}



char *expand(char *token) {

    if (!token || token[0] != '$')

        return strdup(token);



    if (strcmp(token, "$?") == 0) {

        char buf[16];

        snprintf(buf, sizeof(buf), "%d", last_status);

        return strdup(buf);

    }



    if (strcmp(token, "$$") == 0) {

        char buf[16];

        snprintf(buf, sizeof(buf), "%d", getpid());

        return strdup(buf);

    }



    char *val = getenv(token + 1);

    return strdup(val ? val : "");

}


