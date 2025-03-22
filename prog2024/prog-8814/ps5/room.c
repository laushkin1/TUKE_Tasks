#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "room.h"
#include "item.h"

struct room *create_room(char *name, char *description) {
    if (name == NULL || description == NULL ||
        strcmp(name, "") == 0 || strcmp(description, "") == 0 ||
        strlen(name) < 3 || strlen(description) < 5) return NULL;

    struct room *room = (struct room *) malloc(sizeof(struct room));
    if (room == NULL) return NULL;

    room->name = (char *) malloc((strlen(name) + 1) * sizeof(char));
    room->description = (char *) malloc((strlen(description) + 1) * sizeof(char));
    if (room->name == NULL || room->description == NULL) {
        free(room->name);
        free(room->description);
        free(room);
        return NULL;
    }

    strcpy(room->name, name);
    strcpy(room->description, description);
    room->north = NULL;
    room->south = NULL;
    room->east = NULL;
    room->west = NULL;
    room->items = NULL;

    return room;
}

void set_exits_from_room(struct room *room,
                         struct room *north,
                         struct room *south,
                         struct room *east,
                         struct room *west) {
    if (room == NULL) return;
    room->north = north;
    room->east = east;
    room->south = south;
    room->west = west;
}

void show_room(const struct room *room) {
    if (room == NULL) return;
    printf("Room: %s\n", room->description);

    printf("Possible exits:\n");
    if (room->north != NULL) printf("- North\n");
    if (room->south != NULL) printf("- South\n");
    if (room->east != NULL) printf("- East\n");
    if (room->west != NULL) printf("- West\n");
    printf("\n");

    if (room->items == NULL) return;
    printf("Items in the room:\n");
    struct container *items = room->items;
    while (items != NULL) {
        if (items->type == ITEM && items->item != NULL) {
            printf("- %s\n", items->item->name);
        }
        items = items->next;
    }
    printf("\n");
}

struct room *destroy_room(struct room *room) {
    if (room == NULL) return NULL;

    free(room->name);
    free(room->description);

    struct container *current_item = room->items;
    while (current_item != NULL) {
        struct container *temp_item = current_item;
        current_item = current_item->next;
        destroy_item(temp_item->item);
        free(temp_item);
    }

    free(room);

    return NULL;
}

void add_item_to_room(struct room *room, struct item *item) {
    if (room == NULL || item == NULL) return;

    struct container *new_container = (struct container *) malloc(sizeof(struct container));
    if (new_container == NULL) return;

    new_container->type = ITEM;
    new_container->item = item;
    new_container->next = NULL;

    if (room->items == NULL) {
        room->items = new_container;
        return;
    }

    struct container *current_item = room->items;
    while (current_item->next != NULL) current_item = current_item->next;

    current_item->next = new_container;
}

struct item *get_item_from_room(const struct room *room, const char *name) {
    if (room == NULL || name == NULL) return NULL;

    char lowercase_name[strlen(name) + 1];
    for (size_t i = 0, len = strlen(name); i < len; i++)
        lowercase_name[i] = (char) tolower(name[i]);
    lowercase_name[strlen(name)] = '\0';

    struct container *current_item = room->items;
    while (current_item != NULL) {
        if (current_item->type == ITEM && current_item->item != NULL) {
            char lowercase_item_name[strlen(current_item->item->name) + 1];
            for (size_t i = 0, len = strlen(current_item->item->name); i < len; i++)
                lowercase_item_name[i] = (char) tolower(current_item->item->name[i]);
            lowercase_item_name[strlen(current_item->item->name)] = '\0';

            if (strcmp(lowercase_item_name, lowercase_name) == 0) return current_item->item;
        }

        current_item = current_item->next;
    }

    return NULL;
}

void delete_item_from_room(struct room *room, struct item *item) {
    if (room == NULL || item == NULL) return;

    if (room->items->type == ITEM && room->items->item == item) {
        struct container *temp = room->items;
        room->items = room->items->next;
        free(temp);
        return;
    }

    struct container *current_item = room->items;
    while (current_item->next != NULL) {
        if (current_item->next->type == ITEM && current_item->next->item == item) {
            struct container *temp = current_item->next;
            current_item->next = current_item->next->next;
            free(temp);
            return;
        }
        current_item = current_item->next;
    }
}
