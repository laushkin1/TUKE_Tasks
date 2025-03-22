#include <stdio.h>
#include <stdbool.h>

void clear_buffer();

int main(){

    int enter_num;
    int max_num = 0;
    int min_num = 10;
    int sum = 0;

    while (true){
        printf("Enter a num(0-9), to quit enter 0\n");
        scanf("%d", &enter_num);
        clear_buffer();
        if (enter_num == 0){
            break;
        }
        if(enter_num > max_num){
            max_num = enter_num;
        }
        if(enter_num < min_num){
            min_num = enter_num;
        }
        sum = sum + enter_num;
    }

    printf("Sum is: %d\n", sum);
    printf("Max num is: %d\n", max_num);
    printf("Min num is: %d\n", min_num);

    return 0;
}

void clear_buffer(){
    while( getchar() != '\n' );
}

