#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int rand_number();
int get_secret(int, int);
void clear_buffer();
void start_game(int, int, int);


int max_num;
int min_num;


int main(){
    srand(time(NULL));
    int number_A_guessing = (rand() % 100);
    int max_number = (rand() % 100);
    int min_number = (rand() % 100);


    printf("A: I guessing the number, lets play\n");

    start_game((number_A_guessing + max_number), (number_A_guessing - min_number), number_A_guessing);

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

void start_game(int max_number, int min_number, int number_guessing){
    max_num = max_number;
    min_num = min_number;

    int previus_secret = 110;

    while (true){


        int secret = get_secret(min_num, max_num);
        printf("B: Is your secret number %d?\n", secret);

        if (previus_secret == secret){
            continue;
        } else{
            previus_secret = secret;
        }

        if (secret < number_guessing){
            min_num = secret;
            printf("A: No, the guess number is too low\n");
        } else if (secret > number_guessing){
            max_num = secret;
            printf("A: No, the guess number is too high\n");
        } else if (secret == number_guessing){
            printf("A: Yeah, you right\n");
            printf("B: Game over. Your secret number was: %d\n", secret);
            break;
        }
    }
}

