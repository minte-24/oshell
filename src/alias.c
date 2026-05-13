#include "../include/oshell.h"

typedef struct alias {

    char *name;
    char *value;
    struct alias *next;
} alias_t;
static alias_t *alias_list = NULL;

void alias_init(void) {
    alias_list = NULL;
}

void alias_destroy(void) {
    alias_t *cur = alias_list;
    while (cur) {
        alias_t *tmp = cur;
        cur = cur->next;
        free(tmp->name);
        free(tmp->value);
        free(tmp);
    }
}

void alias_set(char *name, char *value) {
    alias_t *cur = alias_list;
    while (cur) {
        if (strcmp(cur->name, name) == 0) {
            free(cur->value);
            cur->value = strdup(value);
            return;
        }
        cur = cur->next;
    }

    alias_t *new_alias = malloc(sizeof(alias_t));
    new_alias->name = strdup(name);
    new_alias->value = strdup(value);
    new_alias->next = alias_list;
    alias_list = new_alias;
}

char *alias_get(char *name) {
    alias_t *cur = alias_list;
    while (cur) {
        if (strcmp(cur->name, name) == 0)
            return cur->value;
        cur = cur->next;
    }
    return NULL;
}

void alias_print(char **args) {
    alias_t *cur = alias_list;

    if (!args[1]) {
        while (cur) {
            printf("%s='%s'\n", cur->name, cur->value);
            cur = cur->next;
        }
        return;
    }

    for (int i = 1; args[i]; i++) {
        cur = alias_list;
        while (cur) {
            if (strcmp(cur->name, args[i]) == 0) {
                printf("%s='%s'\n", cur->name, cur->value);
                break;
            }
            cur = cur->next;
        }
    }
}
