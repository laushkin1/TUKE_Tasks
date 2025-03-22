#include <stdio.h>

int main()
{
    char hello_world[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0'};
    char hello_world2[] = "Hello World!";

    printf("1. %lu\n", sizeof(hello_world));
    printf("2. %lu\n", sizeof(hello_world2));

    return 0;
}