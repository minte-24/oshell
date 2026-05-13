#include "../include/oshell.h"



int builtin_cd(char **args) {

    char cwd[MAX_LINE];

    char *target;



    if (args[2])

        return 1;



    if (!args[1]) {

        target = getenv("HOME");

    } else if (strcmp(args[1], "-") == 0 || strcmp(args[1], "--") == 0) {

        target = getenv("OLDPWD");

        if (!target)

            return 1;

        if (strcmp(args[1], "-") == 0)

            printf("%s\n", target);

    } else {

        target = args[1];

    }



    if (chdir(target) != 0)

        return 1;



    getcwd(cwd, sizeof(cwd));

    setenv("OLDPWD", getenv("PWD"), 1);

    setenv("PWD", cwd, 1);



    return 0;

}



int builtin_exit(char **args) {

    if (args[2])

        return 1;

    exit(args[1] ? atoi(args[1]) : 0);

}



int builtin_env(void) {

    extern char **environ;

    for (char **e = environ; *e; e++)

        puts(*e);

    return 0;

}



int builtin_setenv(char **args) {

    if (!args[1] || !args[2] || args[3])

        return 1;

    return setenv(args[1], args[2], 1);

}



int builtin_unsetenv(char **args) {

    if (!args[1] || args[2])

        return 1;

    return unsetenv(args[1]);

}



int builtin_alias(char **args) {

    if (!args[1]) {

        alias_print(args);

        return 0;

    }



    for (int i = 1; args[i]; i++) {

        char *eq = strchr(args[i], '=');

        if (!eq)

            return 1;



        *eq = '\0';

        char *name = args[i];

        char *value = eq + 1;



        if (*value == '\'' || *value == '"') {

            value++;

            value[strlen(value) - 1] = '\0';

        }



        alias_set(name, value);

    }

    return 0;

}



int builtin_path(char **args) {

    set_path(&args[1]);

    return 0;

}



int is_builtin(char *cmd) {

    return !strcmp(cmd, "cd") ||

           !strcmp(cmd, "exit") ||

           !strcmp(cmd, "env") ||

           !strcmp(cmd, "setenv") ||

           !strcmp(cmd, "unsetenv") ||

           !strcmp(cmd, "alias") ||

           !strcmp(cmd, "path");

}



int run_builtin(char **args) {

    if (!strcmp(args[0], "cd")) return builtin_cd(args);

    if (!strcmp(args[0], "exit")) builtin_exit(args);

    if (!strcmp(args[0], "env")) return builtin_env();

    if (!strcmp(args[0], "setenv")) return builtin_setenv(args);

    if (!strcmp(args[0], "unsetenv")) return builtin_unsetenv(args);

    if (!strcmp(args[0], "alias")) return builtin_alias(args);

    if (!strcmp(args[0], "path")) return builtin_path(args);

    return 1;

}
