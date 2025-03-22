#include <stdio.h>
#include <string.h>

#include "game.h"
#include "world.h"

int main() {
//    printf("Starting program...\n\n");
//
//    // ROOMS
//    printf("Create room (Room)\n");
//    struct room *room = create_room("Room", "This is default room");
//    printf("Room (%s) created success\n", room->name);
//    printf("\n");
//    printf("Create room (EXIT)\n");
//    struct room *exit_room = create_room("EXIT", "This is room for exit");
//    printf("Room (%s) created success\n", exit_room->name);
//    printf("\n");
//
//    // CONTAINERS
//    printf("Create container (first) for room (%s)\n", room->name);
//    struct container *first = create_container(NULL, ROOM, room);
//    printf("Container (first) created success\n");
//    printf("\n");
//    printf("Create container for room (%s)\n", exit_room->name);
//    create_container(first, ROOM, exit_room);
//    printf("Container created success\n");
//    printf("\n");
//
//    // REMOVE CONTAINER/DESTROY ROOM
//    printf("Create room (Room123)\n");
//    struct room *deleted_room = create_room("Room123", "This is room will be deleted");
//    printf("Room (%s) created success\n", deleted_room->name);
//    printf("\n");
//    printf("Create container (container_for_deleted_room) for room (%s)\n", room->name);
//    struct container *container_for_deleted_room = create_container(first, ROOM, deleted_room);
//    printf("Container (container_for_deleted_room) created success\n");
//    printf("\n");
//
//    printf("Remove container (container_for_deleted_room)\n");
//    remove_container(first, container_for_deleted_room);
//    printf("Container (container_for_deleted_room) removed success\n");
//    printf("\n");
//    printf("Destroy room (%s)\n", deleted_room->name);
//    destroy_room(deleted_room);
//    printf("Room (Room123) destroyed success\n");
//    printf("\n");
//
//    // SEARCH FROM CONTAINER
//    printf("Search room (%s) by name from container\n", room->name);
//    struct room *search_room = get_from_container_by_name(first, "room");
//    printf(" Name of search room: %-50s\n", search_room->name);
//    printf("Search room (%s) by name from container was success\n", room->name);
//
//    // SET EXIT TO ROOM
//    printf("\n");
//    printf("Show room (%s)\n", room->name);
//    show_room(room);
//    printf("Room (%s) showed success\n", room->name);
//    printf("\n");
//    printf("Set exit to room (%s)\n", room->name);
//    set_exits_from_room(room, NULL, NULL, exit_room, NULL);
//    printf("Exit to room (%s) added success\n", room->name);
//    printf("\n");
//    printf("Show room (%s)\n", room->name);
//    show_room(room);
//    printf("Room (%s) showed success\n", room->name);
//    printf("\n");
//
//    // ADD ITEM
//    printf("Create item (KLUC)\n");
//    struct item *key = create_item("KLUC", "zlaty KLUC", MOVABLE | USABLE | EXAMINABLE);
//    printf("Item (%s) created success\n", key->name);
//    printf("\n");
//    printf("Add item (%s) to room (%s)\n", key->name, room->name);
//    add_item_to_room(room, key);
//    printf("Item (%s) added success\n", key->name);
//    printf("\n");
//    printf("Show room (%s)\n", room->name);
//    show_room(room);
//    printf("Room (%s) showed success\n", room->name);
//    printf("\n");
//    printf("Some checking\n");
//    if (room->items->item->properties & USABLE)
//        printf("\tYou can use the %s.\n", room->items->item->name);
//    else printf("\tYou can't use the %s.\n", room->items->item->name);
//    printf("\n");
//    if (room->items->item->properties & MOVABLE)
//        printf("\tYou can move the %s.\n", room->items->item->name);
//    else printf("\tYou can't move the %s.\n", room->items->item->name);
//    printf("\n");
//    if (room->items->item->properties & EXAMINABLE)
//        printf("\tYou can examine the %s.\n", room->items->item->name);
//    else printf("\tYou can't examine the %s.\n", room->items->item->name);
//    printf("\n");
//
//    // GET ITEM FROM ROOM
//    printf("Get item (%s) from room (%s)\n", key->name, room->name);
//    struct item *kluc = get_item_from_room(room, "kluc");
//    printf("Item (%s) geted success\n", kluc->name);
//    printf("\n");
//
//    // DELETE ITEM FROM ROOM
//    printf("Delete item (%s) from room (%s)\n", key->name, room->name);
//    delete_item_from_room(room, key);
//    printf("Item (%s) deleted success\n", kluc->name);
//    printf("\n");
//    printf("Show room (%s)\n", room->name);
//    show_room(room);
//    printf("Room (%s) showed success\n", room->name);
//    printf("\n");
//
//    // DESTROY ALL
//    destroy_room(room); // item destroyed here
//    destroy_containers(first);
//
//    // COMMANDS
//    printf("Create command (COMMAND)\n");
//    struct command *command = create_command("COMMAND", "This is command", "(COMMAND)", 1);
//    if (command != NULL) printf("Command (%s) created success\n", command->name);
//    else printf("Error: Command (COMMAND) not created\n");
//    printf("\n");
//    printf("Destroys command (%s)\n", command->name);
//    destroy_command(command);
//    printf("Command (COMMAND) destroys success\n");
//    printf("\n");
//    printf("Create dry command (NULL)\n");
//    struct command *command_null = create_command("NULL", "", "(COMMAND)", 1);
//    if (command_null == NULL) printf("Command (NULL) not created success\n");
//    else printf("Error: Command (%s) is created \n", command_null->name);
//    printf("\n");
//
//    // PARSER
//    printf("Create parser\n");
//    struct parser *my_parser = create_parser();
//    printf("Parser created success\n");
//    printf("\n");
//    printf("Create command\n");
//    struct command *my_command = create_command("command", "Description of the command", NULL, 0);
//    printf("Command created success\n");
//    printf("\n");
//    printf("Create container for command\n");
//    struct container *command_container1 = create_container(NULL, COMMAND, my_command);
//    printf("Container created success\n");
//    printf("\n");
//    if (my_parser != NULL && my_command != NULL && command_container1 != NULL) {
//        if (my_parser->commands == NULL) {
//            printf("This is first container\n");
//            my_parser->commands = command_container1;
//            printf("Container put success\n");
//            printf("\n");
//        } else {
//            printf("This is not a first container\n");
//            struct container *last_container = my_parser->commands;
//            while (last_container->next != NULL) last_container = last_container->next;
//            last_container->next = command_container1;
//            printf("Container put success\n");
//            printf("\n");
//        }
//    } else printf("Error: Unable to add command to the parser.\n");
//
//    printf("Destroy parser\n");
//    my_parser = destroy_parser(my_parser);
//    if (my_parser == NULL) printf("Parser destroyed success\n");
//    else printf("Error: Parser not destroyed\n");
//    printf("\n");
//
//    // BACKPACK
//    printf("Create backpack\n");
//    struct backpack *backpack = create_backpack(1);
//    printf("Backpack created success\n");
//    printf("\n");
//    printf("Add item to backpack\n");
//    struct item *item = create_item("ITEM", "Default item", MOVABLE | USABLE | EXAMINABLE);
//    if (add_item_to_backpack(backpack, item)) printf("Item added success\n");
//    else printf("Error: Item not added\n");
//    printf("\n");
//    printf("Search item in backpack\n");
//    struct item *searched_item = get_item_from_backpack(backpack, "itEm");
//    if (searched_item != NULL) printf("Item searched success\n");
//    else printf("Error: Item not found\n");
//    printf("\n");
//    printf("Delete item from backpack\n");
//    delete_item_from_backpack(backpack, item);
//    printf("Item deleted success\n");
//    printf("\n");
//    destroy_item(item);
//    printf("Destroy backpack\n");
//    backpack = destroy_backpack(backpack);
//    if (backpack == NULL) printf("Backpack destroyed success\n");
//    else printf("Error: Backpack not destroyed\n");
//    printf("\n");
//
//    // WORLD
//    printf("Create world...\n");
//    struct container *world = create_world(0);
//    printf("World created success...\n");
//    printf("\n");
//    printf("Show room (%s)\n", world->room->name);
//    show_room(world->room);
//    printf("Room (%s) showed success\n", world->room->name);
//    printf("\n");
//    printf("Create room (Room558)\n");
//    struct room *new_room = create_room("Room558", "This is default room558");
//    if (new_room != NULL) printf("Room (%s) created success\n", new_room->name);
//    else printf("Error: Room (Room558) not created\n");
//    printf("\n");
//    printf("Add room (%s)\n", new_room->name);
//    add_room_to_world(world, new_room);
//    printf("Room (%s) added success\n", new_room->name);
//    printf("\n");
//    printf("Show room (%s)\n", world->room->name);
//    show_room(world->room);
//    printf("Room (%s) showed success1\n", world->room->name);
//    printf("\n");
//    printf("Get room (%s)\n", "Room 1");
////    struct room *room_from_world = get_room(world, "rOoM 1");
////    printf("Show room (%s)\n", room_from_world->name);
////    show_room(room_from_world);
////    printf("Room (%s) showed success\n", room_from_world->name);
////    printf("Room geted success (%s)\n", room_from_world->name);
//    printf("\n");
//    printf("Destroyed world...\n");
////    world = destroy_world(world);
//    printf("World destroyed success...\n");
//    printf("\n");
//    printf("Starting test...\n");
//    struct room *room1 = create_room("West X Street",
//                                     "West X Street is the rich section of town. So rich, they paved the streets with gold. This probably was not a good idea. The thief guild opened up the next day.");
//    if (room1 != NULL) printf("Room created success\n");
//    struct container *world123 = create_world(0);
//
//    add_room_to_world(world123, room1);
//    struct room *world_room = get_room(world123, room1->name);
//    if (world_room != NULL) {
//        printf("Room found success\n");
//        if (strcmp(world_room->name, room1->name) == 0 && strcmp(world_room->description, room1->description) == 0)
//            printf("Test passed success\n");
//        else printf("Error test to passed\n");
//    } else printf("Error: room not found\n");
//
//    struct game *game123 = create_game(0);
//    struct room *north = create_room("north", "East X Street. It's like X Street, except East.");
//    struct room *south = create_room("south",
//                                     "The blacksmith loudly hammers a new sword over her anvil. Swords, axes, butter knives all line the walls of her workshop, available for a price.");
//    set_exits_from_room(north, NULL, south, NULL, NULL);
//    set_exits_from_room(south, north, NULL, NULL, NULL);
//    game123->current_room = north;
//    struct command *command123 = parse_input(game123->parser, "JUH");
//    execute_command(game123, command123);
//    printf(">>> %s\n", game123->current_room->name);
//
//    // GAME (at the end)
//    printf("Create game\n");
//    struct game *game = create_game(0);
//    printf("Game created success\n");
//    printf("\n");
//    printf("Create command\n");
//    struct command *exit_command = create_command("EXIT", "Type this command if you want to end the game", "(EXIT)", 1);
//    printf("Command created success\n");
//    printf("\n");
//    printf("Create container for command\n");
//    struct container *command_container = create_container(NULL, COMMAND, exit_command);
//    printf("Container created success\n");
//    printf("\n");
//    if (game->parser->commands == NULL) {
//        printf("This is first container\n");
//        game->parser->commands = command_container;
//        printf("Container put success\n");
//        printf("\n");
//    } else {
//        printf("This is not a first container\n");
//        struct container *last_container = game->parser->commands;
//        while (last_container->next != NULL) last_container = last_container->next;
//        last_container->next = command_container;
//        printf("Container put success\n");
//        printf("\n");
//    }
//    printf("Starting game...\n");
//    play_game(game);
//    printf("Game ended success...\n");
//    printf("\n");
//    printf("Destroy game\n");
//    game = destroy_game(game);
//    if (game == NULL) printf("Game destroyed success\n");
//    else printf("Error: Game not destroyed\n");
//    printf("\n");
//
//    printf("Program ended success...\n");

    struct game *game = create_game(0);
    struct command *exit_command = create_command("EXIT", "Type this command if you want to end the game", "(EXIT)", 1);
    play_game(game);

    return 0;
}
