#include <stdlib.h>
#include "game.h"
#include "ui.h"
#include "board.h"

int main() {
    Game *game = create_game();
    read_player_name(game);
    int row, column, mines_count;
    read_size_of_field(&row, &column, &mines_count);
    Board *board = create_board(row, column, mines_count);
    game->board = board;
    play_game(game);
    destroy_game(game);
    exit(EXIT_SUCCESS);
}
