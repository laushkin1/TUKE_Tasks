#include <stdio.h>
#define SIZE 20

int main(){
    char name[SIZE];
    printf("Enter your name\n");
    scanf("%s", name);
//    fgets(name, sizeof(name), stdin);
    printf("Hello your name...\n");
//    printf("Okay its joke, hello %s\n", name);
    printf("Okay its joke, hello %s\n", name);
//    puts(name);
    return 0;
}