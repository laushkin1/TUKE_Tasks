#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include "k.h"

void add_random_tile(struct game *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}

int cmp_by_letter(const void* l1, const void* l2){
    char letter_1 = *(const char*)l1; 
    char letter_2 = *(const char*)l2; 
    
    if (letter_1 < letter_2) return 1;
    else if (letter_1 > letter_2) return -1;
    return 0;
}

bool is_game_won(const struct game game){
    
    char list_board[SIZE*SIZE];
    char k = 'K';

    memcpy(list_board, game.board, sizeof(char)*(SIZE*SIZE));
    qsort(list_board, SIZE*SIZE, sizeof(char), cmp_by_letter);   
    
    if ((char*)bsearch(&k, list_board, SIZE*SIZE, sizeof(char), cmp_by_letter)) return true;
    else return false;
}

bool is_move_possible(const struct game game){

    for(int c = 0; c<SIZE; c++){
        for(int r = 0; r<SIZE; r++){
            if(game.board[c][r] == ' ') return true;

            if(c != SIZE-1 && r != SIZE-1){
                if(game.board[c][r] == game.board[c][r+1] || game.board[c][r] == game.board[c+1][r])
                    return true;
            }
            else if(c != SIZE-1 && r == SIZE-1){
                if(game.board[c][r] == game.board[c+1][r]) return true;
            }
            else if(c == SIZE-1 && r != SIZE-1){
                if(game.board[c][r] == game.board[c][r+1]) return true;
            }
        }
    }

    return false;
}

bool update(struct game *game, int dy, int dx){
    if (dy == dx) return false;
    
    int checker = 0;
    // UP
    if (dy == -1 && dx == 0){
        checker = 0;
        int is_l_first = 1;
        int indx = 0;

        for (int r = 0; r<SIZE; r++){
            int c = 0;

            is_l_first = 1;
            while(c<SIZE){

                if(game->board[c][r] != ' '){
                    if(is_l_first){
                        indx = c;
                        is_l_first--;
                    }
                    else{
                        if(game->board[c][r] == game->board[indx][r]){
                            game->board[indx][r] = (char)(game->board[c][r]+1);
                            game->score += (int)pow(2, (game->board[c][r]+1)-64);
                            checker++;
                            game->board[c][r] = ' ';
                            is_l_first = 1;
                        }
                        else indx = c;
                    }
                }

                c++;
            }
        }
       
        indx = 0;
        for (int r = 0; r<SIZE; r++){
            is_l_first = 1;
            for (int c = 0; c<SIZE; c++){
                if(game->board[c][r] != ' '){
                    if(is_l_first){
                        indx = c;
                        is_l_first--;
                    }
                    else{
                        if(indx+1 != c){
                            game->board[indx+1][r] = game->board[c][r];
                            game->board[c][r] = ' ';
                            checker++;
                        }
                        indx++;
                    }
                } 
                else if(c == 0){
                    indx = -1;
                    is_l_first--;
                }
            }
        }
        if(checker) return true;
        else return false;
    }

    // DOWN
    if (dy == 1 && dx == 0){
        checker = 0;
        int is_l_first = 1;
        int indx = 0;

        for (int r = 0; r<SIZE; r++){
            int c = SIZE;

            is_l_first = 1;
            while(c>0){
                c--;

                if(game->board[c][r] != ' '){
                    if(is_l_first){
                        indx = c;
                        is_l_first--;
                    }
                    else{
                        if(game->board[c][r] == game->board[indx][r]){
                            game->board[indx][r] = (char)(game->board[c][r]+1);
                            game->score += (int)pow(2, (game->board[c][r]+1)-64);
                            checker++;
                            game->board[c][r] = ' ';
                            is_l_first = 1;
                        }
                        else indx = c;
                    }
                }
            }
        }
       
        indx = 0;
        for (int r = 0; r<SIZE; r++){
            is_l_first = 1;
            for (int c = SIZE-1; c>=0; c--){
                if(game->board[c][r] != ' '){
                    if(is_l_first){
                        indx = c;
                        is_l_first--;
                    }
                    else{
                        if(indx-1 != c){
                            game->board[indx-1][r] = game->board[c][r];
                            game->board[c][r] = ' ';
                            checker++;
                        }
                        indx--;
                    }
                }
                else if(c == SIZE-1){
                    indx = SIZE;
                    is_l_first--;
                }
            }
        }
        if(checker) return true;
        else return false;
    }

    // LEFT
    if (dx == -1 && dy == 0){
        checker = 0;
        int is_l_first = 1;
        int indx = 0;

        for (int c = 0; c<SIZE; c++){
            int r = 0;
            
            is_l_first = 1;
            while(r<SIZE){

                if(game->board[c][r] != ' '){
                    if(is_l_first){
                        indx = r;
                        is_l_first--;
                    }
                    else{
                        if(game->board[c][r] == game->board[c][indx]){
                            game->board[c][indx] = (char)(game->board[c][r]+1);
                            game->score += (int)pow(2, (game->board[c][r]+1)-64);
                            game->board[c][r] = ' ';
                            checker++;
                            is_l_first = 1;
                        }
                        else indx = r;
                    }
                }

                r++;
            }
        }
 
        indx = 0;
        for (int c = 0; c<SIZE; c++){
            is_l_first = 1;
            for (int r = 0; r<SIZE; r++){
                if(game->board[c][r] != ' '){
                    if(is_l_first){
                        indx = r;
                        is_l_first--;
                    }
                    else{
                        if(indx+1 != r){
                            game->board[c][indx+1] = game->board[c][r];
                            game->board[c][r] = ' ';
                            checker++;
                        }
                        indx++;
                    }
                }
                else if(r == 0){
                    is_l_first--;
                    indx=-1;
                }

            }
        }

        if(checker) return true;
        else return false;
    }

    // RIGHT
    if (dx == 1 && dy == 0){
        checker = 0;
        int is_l_first = 1;
        int indx = 0;

        for (int c = 0; c<SIZE; c++){
            int r = SIZE;

            is_l_first = 1;
            while(r>0){

                r--;
                
                if(game->board[c][r] != ' '){
                    if(is_l_first){
                        indx = r;
                        is_l_first--;
                    }
                    else{
                        if(game->board[c][r] == game->board[c][indx]){
                            game->board[c][indx] = (char)(game->board[c][r]+1);
                            game->score += (int)pow(2, (game->board[c][r]+1)-64);
                            game->board[c][r] = ' ';
                            checker++;
                            is_l_first = 1;
                        }
                        else indx = r;
                    }
                }
            }
        }

        indx = 0;
        for (int c = 0; c<SIZE; c++){
            is_l_first = 1;
            for (int r = SIZE-1; r>=0; r--){
                if(game->board[c][r] != ' '){
                    if(is_l_first){
                        indx = r;
                        is_l_first--;
                    }
                    else{
                        if(indx-1 != r){
                            game->board[c][indx-1] = game->board[c][r];
                            game->board[c][r] = ' ';
                            checker++;
                        }
                        indx--;
                    }
                }
                else if(r == SIZE-1){
                    is_l_first--;
                    indx=SIZE;
                }
            }
        }
        if(checker) return true;
        else return false;
    }
    return false;
}

