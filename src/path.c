#include "../include/oshell.h"



static char **path_list = NULL;

static int path_count = 0;



void free_path(void) {

    if (!path_list)

        return;



    for (int i = 0; i < path_count; i++)

        free(path_list[i]);



    free(path_list);

    path_list = NULL;

    path_count = 0;

}



void init_path(void) {

    free_path();

    path_list = malloc(sizeof(char *));

    path_list[0] = strdup("/bin");

    path_count = 1;

}



void set_path(char **dirs) {

    free_path();



    int count = 0;

    while (dirs && dirs[count])

        count++;



    if (count == 0) {

        path_list = NULL;

        path_count = 0;

        return;

    }



    path_list = malloc(sizeof(char *) * count);

    for (int i = 0; i < count; i++)

        path_list[i] = strdup(dirs[i]);



    path_count = count;

}



char *find_cmd(char *cmd) {

    if (!path_list || path_count == 0)

        return NULL;



    for (int i = 0; i < path_count; i++) {

        char full[MAX_LINE];

        snprintf(full, sizeof(full), "%s/%s", path_list[i], cmd);



        if (access(full, X_OK) == 0)

            return strdup(full);

    }

    return NULL;

}
