#include "game.h"
#include "world.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct game *create_game() {
    struct game *game = (struct game *) malloc(sizeof(struct game));
    if (game == NULL) return NULL;
    game->state = PLAYING;
    game->parser = create_parser();
    if (game->parser == NULL) {
        free(game);
        return NULL;
    }
    game->backpack = create_backpack(5); // can be changed
    if (game->backpack == NULL) {
        destroy_parser(game->parser);
        free(game);
        return NULL;
    }

    game->world = create_world();
    game->current_room = game->world->room;

    return game;
}

struct game *destroy_game(struct game *game) {
    if (game == NULL) return NULL;

    game->state = GAMEOVER;

    destroy_parser(game->parser);
    destroy_containers(game->world);
    destroy_room(game->current_room);
    destroy_backpack(game->backpack);

    free(game);

    return NULL;
}

void play_game(struct game *game) {
    if (game == NULL) {
        printf("Error: Game is not initialized.\n");
        return;
    }
    char input[INPUT_BUFFER_SIZE];
    struct command *player_command;

    // Game loop
    while (game->state == PLAYING) {
        printf("Enter your command: ");
        fgets(input, INPUT_BUFFER_SIZE, stdin);
        input[strcspn(input, "\n")] = '\0';
        player_command = parse_input(game->parser, input);

        execute_command(game, player_command);
    }

    if (game->state == GAMEOVER) printf("Game Over!\n");
    else if (game->state == SOLVED) printf("Congratulations! You solved the game.\n");
    else if (game->state == RESTART) {
        printf("Restarting the game...\n");
        // TODO add restart game logic
        game->state = PLAYING;
        play_game(game);
    }
}


void execute_command(struct game *game, struct command *command) {
    if (game == NULL) {
        printf("Error: Invalid game.\n");
        return;
    }
    if (command == NULL) {
        printf("Error: Invalid command.\n");
        return;
    }
    // TODO Write a function, add all command and logic

    if (strcmp(command->name, "EXIT") == 0 || strcmp(command->name, "KONIEC") == 0) {
        game->state = GAMEOVER;
        return;
    } else if (strcmp(command->name, "JUH") == 0) {
        if (game->current_room->south == NULL) {
            printf("There is no this escape!\nzr");
            return;
        }
        game->current_room = game->current_room->south;
    } else if (strcmp(command->name, "ZAPAD") == 0) {
        if (game->current_room->west == NULL) {
            printf("There is no this escape!\n");
            return;
        }
        game->current_room = game->current_room->west;
    } else if (strcmp(command->name, "RESTART") == 0) {
        game->state = RESTART;
        return;
    }
}