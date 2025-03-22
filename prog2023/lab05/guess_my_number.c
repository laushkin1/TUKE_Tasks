#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int get_secret(int, int);
void clear_buffer();
void start_game();

int max_num;
int min_num;


int main(){
    printf("Please think of a number between %d and %d!\n", max_num, min_num);

    start_game();

    return 0;
}


int get_secret(const int start, const int end){
    int end_num = (start - end) - 1;
    srand(time(NULL));
    int secret = (rand() % end_num) + start;

    return secret;
}

void clear_buffer(){
    while( getchar() != '\n' );
}

void start_game(){
    char answer;
    max_num = 100;
    min_num = 0;

    while (true){

        int secret = get_secret(min_num, max_num);
        printf("Is your secret number %d?\n", secret);
        printf("\tEnter 'h' to indicate the guess is too high. \n\tEnter 'l' to indicate the guess is too low. \n\tEnter 'c' to indicate I guessed correctly.\n");
        scanf("%c", &answer);
        clear_buffer();

        if (answer == 'l'){
            min_num = secret;
        } else if (answer == 'h'){
            max_num = secret;
        } else if (answer == 'c'){
            printf("Game over. Your secret number was: %d\n", secret);
            break;
        }
    }
}