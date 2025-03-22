#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "backpack.h"

struct backpack *create_backpack(const int capacity) {
    struct backpack *backpack = (struct backpack *) malloc(sizeof(struct backpack));
    if (backpack == NULL) return NULL;

    backpack->capacity = capacity;
    backpack->size = 0;
    backpack->items = NULL;

    return backpack;
}

struct backpack *destroy_backpack(struct backpack *backpack) {
    if (backpack == NULL) return NULL;

    struct container *currect_item = backpack->items;
    while (currect_item != NULL) {
        struct container *next_item = currect_item->next;
        destroy_containers(currect_item);
        currect_item = next_item;
    }

    free(backpack);
    return NULL;
}

bool add_item_to_backpack(struct backpack *backpack, struct item *item) {
    if (backpack == NULL || item == NULL ||
        backpack->size >= backpack->capacity ||
        !(item->properties & MOVABLE)) return false;


    struct container *container = create_container(NULL, ITEM, item);
    if (backpack->items == NULL) backpack->items = container;
    else {
        struct container *current_container = backpack->items;
        while (current_container->next != NULL) current_container = current_container->next;
        current_container->next = container;
    }
    backpack->size++;
    return true;
}

struct item *get_item_from_backpack(const struct backpack *backpack, char *name) {
    if (backpack == NULL || backpack->items == NULL || name == NULL) return NULL;

    char lowercase_name[strlen(name) + 1];
    for (size_t i = 0, len = strlen(name); i < len; i++)
        lowercase_name[i] = (char) tolower(name[i]);
    lowercase_name[strlen(name)] = '\0';

    struct container *current_item = backpack->items;
    while (current_item != NULL) {
        char lowercase_item_name[strlen(current_item->item->name) + 1];
        for (size_t i = 0, len = strlen(current_item->item->name); i < len; i++)
            lowercase_item_name[i] = (char) tolower(current_item->item->name[i]);
        lowercase_item_name[strlen(current_item->item->name)] = '\0';

        if (strcmp(lowercase_item_name, lowercase_name) == 0) return current_item->item;

        current_item = current_item->next;
    }

    return NULL;
}

void delete_item_from_backpack(struct backpack *backpack, struct item *item) {
    if (backpack == NULL || item == NULL || backpack->items == NULL) return;

    struct container *current_item = backpack->items;
    struct container *prev_item = NULL;

    while (current_item != NULL) {
        if (current_item->item == item) {
            if (prev_item == NULL)
                backpack->items = current_item->next;
            else
                prev_item->next = current_item->next;
            free(current_item);
            backpack->size--;
            return;
        }

        prev_item = current_item;
        current_item = current_item->next;
    }
}