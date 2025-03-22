#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "ui.h"
#include "view.h"
#include "str_utils.h"

#define HOF_FILENAME "score.txt"

/* private functions */
void game_loop(Game *game);
void print_play_field(Game *game, int input_row, int input_column);
void print_score(Player *list_of_players, int number_of_all_players);
void print_input_rules();
void mark_tile_as_mine(Game *game, int input_row, int input_column);


// Ask a player size of the field and amount of mines on the field
void read_size_of_field(int *row, int *column, int *mines_count) {
    int input, input_row = 9, input_column = 9, input_mines = 9;

    printf("Zadajte počet riadkov(väčší ako 0 a menej ako 10): \n");
    while ((input = scanf("%d", &input_row)) == 0 || input_row == 0 || input_row >= 10) {
        scanf("%*[^\n]");
    }
    *row = input_row;

    printf("Zadajte počet stĺpcov(väčší ako 0 a menej ako 10): \n");
    while ((input = scanf("%d", &input_column)) == 0 || input_column == 0 || input_column >= 10) {
        scanf("%*[^\n]");
    }
    *column = input_column;
    printf("Zadajte počet mín(väčší ako 0): \n");
    while ((input = scanf("%d", &input_mines)) == 0 || input_mines == 0 ||
           input_mines > (input_row * input_column) - 1) {
        scanf("%*[^\n]");
    }
    *mines_count = input_mines;
}

void reset_game(Game *game) {
    assert(game != NULL);
    assert(game->board != NULL);

    // Reset player's score
    game->player->score = 1;

    // Resetting the game board
    destroy_board(game->board);
    int row, column, mines_count;
    read_size_of_field(&row, &column, &mines_count);
    Board *board = create_board(row, column, mines_count);
    game->board = board;

    // Reset game state
    game->game_state = PLAYING;
}

/**
 * Ask a player for his name and store in the game.
 */
void read_player_name(Game *game) {
    assert(game != NULL);
    printf("Zadajte vaše meno prosím: \n");
    char name_of_player[MAX_PLAYER_LENGTH];
    fgets(name_of_player, MAX_PLAYER_LENGTH, stdin);
    str_remove_spaces(name_of_player);
    strcpy(game->player->name, name_of_player);
}


/**
 * Handle whole process of the Game
 */
void play_game(Game *game) {
    assert(game != NULL);

    Player list_of_players[PLAYERS_LIMIT];
    int size_of_list = read_scores(HOF_FILENAME, list_of_players);
    if (size_of_list > 0) {
        print_score(list_of_players, size_of_list);
    }

    do {
        // Main game loop
        game_loop(game);

        // Display game result
        if (game->game_state == SOLVED) {
            printf("Congratulations %s. Solution is correct!\n", game->player->name);
        } else {
            printf("Sorry %s. Solution is incorrect!\n", game->player->name);
        }
        printf("Your score is: %d\n", game->player->score);

        // Handling player score and leaderboard
        bool is_player_added_to_list = add_player_to_list(list_of_players, &size_of_list, *game->player);

        if (is_player_added_to_list) {
            save_scores(HOF_FILENAME, list_of_players, size_of_list);
        }

        // Asking for replay
        char play_again;
        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &play_again);

        // Clear the input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (play_again == 'y' || play_again == 'Y' ||
            (play_again == 'e' && getchar() == 'y') ||
            (play_again == 's' && getchar() == 'y')) {
            // Resetting the game and board to start a new game
            reset_game(game);
        } else {
            break;
        }

    } while (1); // Exit loop condition, you can use other conditions
}


/**
 * Handles players input process
 * Loops until game state is playing
 */
void game_loop(Game *game) {
    assert(game != NULL);
    int input, input_row = -1, input_column = -1;
    bool is_move_first = true;
    char action;

    do {
        print_play_field(game, input_row, input_column);
        print_input_rules();

        while ((input = scanf("%c %d %d", &action, &input_row, &input_column)) == 0) {
            scanf("%*[^\n] %*[^\n] %*[^\n]");
            print_input_rules();
        }
        if (input != EOF) {
            if (is_input_data_correct(game->board, input_row - 1, input_column - 1)) {
                if (action == 'm' || action == 'M') {
                    if (game->board->tiles[input_row - 1][input_column - 1]->tile_state == MARKED)
                        game->board->tiles[input_row - 1][input_column - 1]->tile_state = CLOSED;
                    else mark_tile_as_mine(game, input_row - 1, input_column - 1);
                } else if (action == 'o' || action == 'O') {
                    if (game->board->tiles[input_row - 1][input_column - 1]->tile_state == MARKED)
                        printf("Nemôžete otvoriť dlaždicu, ktorá je označená ako mina.\n");

                    // if input is not empty and is correct then open the tile
                    if (is_move_first) {
                        is_move_first = false;
                        if (game->board->tiles[input_row - 1][input_column - 1]->is_mine)
                            game->board->tiles[input_row - 1][input_column - 1]->tile_state = OPEN;
                    }
                    open_tile(game, (input_row - 1), input_column - 1);
                } else printf("Nesprávny postup! Zadaním <o> otvoríte dlaždicu alebo <m> označíte mínu.\n");
            }
        }
    } while (game->game_state == PLAYING);
    print_play_field(game, input_row, input_column);
}


void print_score(Player *list_of_players, int number_of_all_players) {
    char *text = view_hof(list_of_players, number_of_all_players);
    printf("%s", text);
    free(text);
}

void print_play_field(Game *game, int input_row, int input_column) {
    char *field = view_play_field(game->board, input_row, input_column);
    printf("\n%s\n", field);
    free(field);
}


void print_input_rules() {
    printf("Vedenie <o> na otvorenie dlaždíc a <m> na označenie mín.\n"
           "  Zadajte číslo riadka, medzeru a číslo stĺpca.\n"
           "  Napr. o 2 3 alebo m 5 9\n");
}
