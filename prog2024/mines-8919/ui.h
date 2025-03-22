#ifndef MINES_UI_H
#define MINES_UI_H

#include "game.h"

void game_loop(Game *game);
void reset_game(Game *game);
void read_player_name(Game *game);
void play_game(Game *game);
void read_size_of_field(int *row, int *column, int *mines_count);

#endif // MINES_UI_H
