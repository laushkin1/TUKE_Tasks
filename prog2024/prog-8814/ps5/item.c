#include <stdlib.h>
#include <string.h>

#include "item.h"

struct item *create_item(char *name, char *description, unsigned int properties) {
    if (name == NULL || description == NULL ||
        strcmp(name, "") == 0 || strcmp(description, "") == 0 ||
        strlen(name) < 3 || strlen(description) < 5) return NULL;
    if (properties & ~(unsigned int)(USABLE | EXAMINABLE | OPENABLE | MOVABLE)) return NULL;

    struct item *new_item = (struct item *) malloc(sizeof(struct item));
    if (new_item == NULL) return NULL;

    new_item->name = (char *) malloc((strlen(name) + 1) * sizeof(char));
    new_item->description = (char *) malloc((strlen(description) + 1) * sizeof(char));
    if (new_item->name == NULL || new_item->description == NULL) {
        free(new_item->name);
        free(new_item->description);
        free(new_item);
        return NULL;
    }

    strcpy(new_item->name, name);
    strcpy(new_item->description, description);
    new_item->properties = properties;

    return new_item;
}

struct item *destroy_item(struct item *item) {
    if (item != NULL) {
        free(item->name);
        free(item->description);
        free(item);
    }
    return NULL;
}