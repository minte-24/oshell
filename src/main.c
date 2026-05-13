#include "../include/oshell.h"



int main(int argc, char *argv[]) {

    FILE *input = stdin;

    char line[MAX_LINE];



    if (argc > 2) {

        print_error();

        exit(1);

    }



    signal(SIGINT, SIG_IGN);



    init_path();

    alias_init();



    if (argc == 2) {

        input = fopen(argv[1], "r");

        if (!input) {

            print_error();

            exit(1);

        }

    }



    while (1) {

        if (input == stdin)

            printf("$ ");



        if (!fgets(line, sizeof(line), input))

            break;



        execute_line(line);

    }



    if (input != stdin)

        fclose(input);



    free_path();

    alias_destroy();



    return 0;

}


