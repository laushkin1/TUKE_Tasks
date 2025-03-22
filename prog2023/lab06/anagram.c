#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 50

void prepare_string(char* input);
void remove_spaces(char *str);


int main()
{
    char buffer[BUFFER_SIZE];
    fgets(buffer, sizeof(buffer), stdin);

    // ...
    prepare_string(buffer);

    char delim[] = " "; // space as delimiter

    char *token = strtok(buffer, delim); // first word
    char first_part[strlen(token) + 1];
    strcpy(first_part, token); // terminator is added by strcpy

    token = strtok(NULL, delim); // second word
    char second_part[strlen(token) + 1];
    strcpy(second_part, token);
// ...
    return 0;
}

void prepare_string(char* input) {
    if (input == NULL)
    {
        return;
    }

    int len = strlen(input);

    for (int i = 0; i < len; i++)
    {
        if (isalpha(input[i]))
        {
            input[i] = tolower(input[i]);
        }

    }

}

void remove_spaces(char *str) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}