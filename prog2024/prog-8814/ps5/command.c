#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "command.h"

struct command *create_command(char *name, char *description, char *pattern, size_t nmatch) {
    if (name == NULL || description == NULL ||
        strcmp(name, "") == 0 || strcmp(description, "") == 0 ||
        strlen(name) < 3 || strlen(description) < 5) return NULL;

    struct command *command = (struct command *) malloc(sizeof(struct command));
    if (command == NULL) return NULL;

    command->name = (char *) malloc((strlen(name) + 1) * sizeof(char));
    command->description = (char *) malloc((strlen(description) + 1) * sizeof(char));
    if (command->name == NULL || command->description == NULL) {
        free(command->name);
        free(command->description);
        free(command);
        return NULL;
    }

    strcpy(command->name, name);
    strcpy(command->description, description);


    if (pattern != NULL && nmatch > 0) {
        if (regcomp(&command->preg, pattern, REG_EXTENDED) != 0) {
            free(command->name);
            free(command->description);
            free(command);
            return NULL;
        }
        command->nmatch = nmatch;
        command->groups = (char **) malloc(nmatch * sizeof(char *));
        if (command->groups == NULL) {
            free(command->name);
            free(command->description);
            regfree(&command->preg);
            free(command);
            return NULL;
        }
    } else {
        command->nmatch = 0;
        command->groups = NULL;
    }

    return command;
}

struct command *destroy_command(struct command *command) {
    if (command == NULL) return NULL;

    free(command->name);
    free(command->description);

    if (command->nmatch > 0) {
        regfree(&command->preg);
        free(command->groups);
    }

    free(command);

    return NULL;
}
