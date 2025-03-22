#include <stdio.h>
#include <string.h>
#include "k.h"
#include "hof.h"

void print_board(struct game game);

int main() {
    struct player list[10];
    int size = load(list);
    char user_name[30];

    printf("Enter your name\n: ");
    scanf("%29s", user_name);
    printf("\n\n");

    struct player player;
    strcpy(player.name, user_name);
    player.score = 0;

    struct game game = {

            .board = {
                    {' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' '}
            },
            .score = 0
    };

    while (!is_game_won(game)) {
        add_random_tile(&game);
        if (is_move_possible(game)) {
            printf("\n");
            char user_input;
            int updaten = 0;
            do {
                print_board(game);
                printf("Please enter letter to move\n(w)Up (s)Down (d)Right (a)Left\n: ");
                scanf(" %c", &user_input);
                printf("\n");
                if (user_input == 'w') updaten = update(&game, -1, 0);
                else if (user_input == 's') updaten = update(&game, 1, 0);
                else if (user_input == 'a') updaten = update(&game, 0, -1);
                else if (user_input == 'd') updaten = update(&game, 0, 1);
                else if (user_input == 'q') {
                    printf("Thank you for play!\nYour score: %d\n", game.score);
                    player.score = game.score;
                    if (add_player(list, &size, player)) {
                        printf("\nCongratilation, you get at The Hole Of Fame\n");
                        if (save(list, size))
                            for (int i = 0; i < size; i++)
                                printf("%2d. %-*s\t%5d\n", i + 1, 30, list[i].name, list[i].score);
                        else
                            printf("Sorry, there is some error, we can't open the score file and save you\n");
                    }
                    return 0;
                }
            } while (!updaten);
        } else {
            printf("You lose!\nYour score: %d\n", game.score);
            player.score = game.score;
            if (add_player(list, &size, player)) {
                printf("\nCongratilation, you get at The Hole Of Fame\n");
                if (save(list, size))
                    for (int i = 0; i < size; i++) printf("%2d. %-*s\t%5d\n", i + 1, 30, list[i].name, list[i].score);
                else
                    printf("Sorry, there is some error, we can't open the score file and save you\n");
            }
            return 0;
        }
    }
    printf("You win!\nYour score: %d\n", game.score);
    player.score = game.score;
    if (add_player(list, &size, player)) {
        printf("\nCongratilation, you get at The Hole Of Fame\n");
        if (save(list, size))
            for (int i = 0; i < size; i++) printf("%2d. %-*s\t%5d\n", i + 1, 30, list[i].name, list[i].score);
        else
            printf("Sorry, there is some error, we can't open the score file and save you\n");
    }

    return 0;
}

void print_board(struct game game) {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("| %c ", game.board[i][j]);
        }
        printf("|\n");
    }
    printf("\n");

    printf("Good");
}