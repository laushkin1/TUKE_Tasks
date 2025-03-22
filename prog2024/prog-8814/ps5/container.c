#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "container.h"

struct container *create_container(struct container *first, enum container_type type, void *entry) {
    if (entry == NULL || (first != NULL && first->type != type)) return NULL;

    struct container *container = (struct container *) malloc(sizeof(struct container));
    if (container == NULL) return NULL;
    container->type = type;

    if (type == ROOM) {
        container->room = (struct room *) entry;
    } else if (type == ITEM) {
        container->item = (struct item *) entry;
    } else if (type == COMMAND) {
        container->command = (struct command *) entry;
    } else if (type == TEXT) {
        container->text = (char *) entry;
    } else {
        free(container);
        return NULL;
    }

    container->next = NULL;
    if (first == NULL) return container;

    struct container *current = first;
    while (current->next != NULL) current = current->next;
    current->next = container;

    return container;
}

struct container *destroy_containers(struct container *first) {
    while (first != NULL) {
        struct container *temp = first;
        first = first->next;
        if (temp->type == TEXT) free(temp->text);
        free(temp);
    }

    return NULL;
}

void *get_from_container_by_name(struct container *first, const char *name) {
    if (name == NULL || first == NULL ||
        strcmp(name, "") == 0 || strlen(name) < 3) return NULL;

    char lowercase_name[strlen(name) + 1];
    for (size_t i = 0, len = strlen(name); i < len; i++)
        lowercase_name[i] = (char) tolower(name[i]);
    lowercase_name[strlen(name)] = '\0';

    while (first != NULL) {
        if (first->type == ROOM && first->room != NULL) {
            char lowercase_room_name[strlen(first->room->name) + 1];
            for (size_t i = 0, len = strlen(first->room->name); i < len; i++)
                lowercase_room_name[i] = (char) tolower(first->room->name[i]);
            lowercase_room_name[strlen(first->room->name)] = '\0';

            if (strcmp(lowercase_room_name, lowercase_name) == 0) return first->room;

        } else if (first->type == ITEM && first->item != NULL) {
            char lowercase_item_name[strlen(first->item->name) + 1];
            for (size_t i = 0, len = strlen(first->item->name); i < len; i++)
                lowercase_item_name[i] = (char) tolower(first->item->name[i]);
            lowercase_item_name[strlen(first->item->name)] = '\0';

            if (strcmp(lowercase_item_name, lowercase_name) == 0) return first->item;

        } else if (first->type == COMMAND && first->command != NULL) {
            char lowercase_command_name[strlen(first->command->name) + 1];
            for (size_t i = 0, len = strlen(first->command->name); i < len; i++)
                lowercase_command_name[i] = (char) tolower(first->command->name[i]);
            lowercase_command_name[strlen(first->command->name)] = '\0';

            if (strcmp(lowercase_command_name, lowercase_name) == 0) return first->command;

        } else if (first->type == TEXT && first->text != NULL) {
            char lowercase_text[strlen(first->text) + 1];
            for (size_t i = 0, len = strlen(first->text); i < len; i++)
                lowercase_text[i] = (char) tolower(first->text[i]);
            lowercase_text[strlen(first->text)] = '\0';

            if (strcmp(lowercase_text, lowercase_name) == 0) return first->text;

        }

        first = first->next;
    }

    return NULL;
}

struct container *remove_container(struct container *first, void *entry) {
    if (first == NULL) return NULL;

    if (first->room == entry || first->item == entry ||
        first->command == entry || first->text == entry) {

        struct container *temp = first;
        first = first->next;
        free(temp);
        return first;

    }

    struct container *current = first;
    while (current->next != NULL) {
        if (current->next->room == entry || current->next->item == entry ||
            current->next->command == entry || current->next->text == entry) {

            struct container *temp = current->next;
            current->next = current->next->next;
            free(temp);
            return first;

        }
        current = current->next;
    }

    return first;
}
