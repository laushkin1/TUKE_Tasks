#include <stdio.h>
#include <string.h>

void draw(const int size, char field[]);
int add_cross(const int size, char field[], const int position);
int is_solved(const int size, char field[]);

int main(){
    char my_field[15];
    int size300;

    printf("Enter the size of field: ");
    scanf("%d", &size300);
    if (4 <= size300 && size300 <= 9){
        my_field[size300] = '\0';

        for (int i=0; i<size300; i++){
            my_field[i] = ' ';
        }
    } else{
        printf("Wrong size\n");
        return 1;
    }

    while (1){
        int posA = 0;
        draw(size300, my_field);
        printf("Player A: ");
        scanf("%d", &posA);
        if (add_cross(size300, my_field, posA) == -1){
            printf("Wrong position!\n");
        } else{
            if(is_solved(size300, my_field)){
                printf("Player A wins!\n");
                break;
            }
            printf("\n");
            draw(size300, my_field);
        }
        if(is_solved(size300, my_field)){
            break;
        }

        int posB = 0;
        printf("Player B: ");
        scanf("%d", &posB);
        if (add_cross(size300, my_field, posB) == -1){
            printf("Wrong position!\n");
        } else{
            if(is_solved(size300, my_field)){
                printf("Player B wins!\n");
                break;
            }
            printf("\n");
            draw(size300, my_field);
        }
    }

    return 0;
}

void draw(const int size, char field[]){
    if (4 > size || size > 9){
        return;
    }

    int walllen = (size*2) + 1;

    for (int i = 0; i<walllen; i++){
        if(i%2){
            printf("-");
        } else{
            printf("+");
        }
    }
    printf("\n");

    for (int i = 0; i< strlen(field); i++){
        printf("|%c", field[i]);
    }
    printf("|");
    printf("\n");

    for (int i = 0; i< walllen; i++){
        if(i%2){
            printf("-");
        } else{
            printf("+");
        }
    }
    printf("\n");

    int n = 1;
    for (int i = 0; i<walllen; i++) {
        if (i % 2) {
            printf("%d", n);
            n++;
        } else{
            printf(" ");
        }
    }
    printf("\n");
}

int add_cross(const int size, char field[], const int position){
    if(position < 1 || position > size){
        return -1;
    }
    int indx = position - 1;
    if (field[indx] == ' '){
        field[indx] = 'X';
    } else{
        return 0;
    }
    return 1;
}

int is_solved(const int size, char field[]){
    int count = 0;
    for (int i = 0; i<size; i++){
        if (count == 3){
            return 1;
        }
        if (field[i] == 'X'){
            count++;
        } else{
            count = 0;
        }
    }
    return 0;
}