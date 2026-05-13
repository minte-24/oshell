#include "../include/oshell.h"



int execute_single(char **args, char *redir) {

    if (!args || !args[0]) return 0;



    char *alias_val = alias_get(args[0]);

    if (alias_val)

        args[0] = alias_val;



    if (is_builtin(args[0]))

        return run_builtin(args);



    char *cmd = find_cmd(args[0]);

    if (!cmd) {

        print_error();

        return 127;

    }



    pid_t pid = fork();

    if (pid == 0) {

        if (redir) {

            int fd = open(redir, O_CREAT | O_WRONLY | O_TRUNC, 0666);

            if (fd < 0) exit(1);

            dup2(fd, STDOUT_FILENO);

            dup2(fd, STDERR_FILENO);

            close(fd);

        }

        execv(cmd, args);

        exit(126);

    }



    int status;

    waitpid(pid, &status, 0);

    free(cmd);



    if (WIFEXITED(status))

        return WEXITSTATUS(status);



    return 1;

}



int execute_parallel(char ***cmds, int count) {

    pid_t pids[count];



    for (int i = 0; i < count; i++) {

        pids[i] = fork();
if (pids[i] == 0) {

            execute_single(cmds[i], NULL);

            exit(0);

        }

    }



    for (int i = 0; i < count; i++)

        waitpid(pids[i], NULL, 0);



    return 0;

}
