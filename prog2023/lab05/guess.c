#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define MAX_NUMBER 100
#define MIN_NUMBER 1
#define MAX_ATTEMPTS 5

int get_guess();
int get_secret(int, int);
void clear_buffer();
void start_game();


int main(){
    printf("Pick a number between 1 and %d. \nYou have max. 5 attempts.\n", MAX_NUMBER);

    start_game();

    return 0;
}

int get_guess(){
    printf(">>> ");

    int guess;
    scanf("%d", &guess);

    return guess;
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
    int secret = get_secret(MIN_NUMBER, MAX_NUMBER);
    int steps_count = 0;
    char answer;

    while (true){

        int guess = get_guess();

        steps_count++;

        if (guess == secret){
            printf("Congratulations!\n");
            printf("You won in %d steps.\n", steps_count);
            printf("Play again? (y/n) ");
            clear_buffer();
            scanf("%c", &answer);
            clear_buffer();

            if (answer == 'n') {
                break;
            } else if (answer == 'y'){
                steps_count = 0;
                secret = get_secret(MIN_NUMBER, MAX_NUMBER);
                printf("Pick a number between 1 and %d. \nYou have max. 5 attempts.\n", MAX_NUMBER);
            } else{
                printf("Invalid value, programme stops.\n");
                break;
            }

        } else if (steps_count >= MAX_ATTEMPTS){
            printf("Game Over. Number is: %d\n", secret);
            printf("Play again? (y/n) ");
            clear_buffer();
            scanf("%c", &answer);
            clear_buffer();

            if (answer == 'n') {
                break;
            } else if (answer == 'y'){
                steps_count = 0;
                secret = get_secret(MIN_NUMBER, MAX_NUMBER);
                printf("Pick a number between 1 and %d. \nYou have max. 5 attempts.\n", MAX_NUMBER);
            } else{
                printf("Invalid value, programme stops.");
                break;
            }

        } else if (secret < guess && guess < (MAX_NUMBER + 1)){
            printf("Too many, my number is smaller than yours. Try again\n");
        } else if (secret > guess && guess > (MIN_NUMBER - 1)){
            printf("Too little, my number is bigger than yours. Try again\n");
        } else{
            printf("Number is out of range, please try again\n");
        }
    }
}
