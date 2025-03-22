#include <stdbool.h>
#include <string.h>

int str_num_to_int_num(char* num){
    int len = strlen(num), result = 0, i;

    for(i = 0; i<len; i++) result = result * 10 + ( num[i] - '0' );
    return result;
}

bool is_valid_ip(const char * addr) {
    int lenad = strlen(addr);
    char addr_copy[lenad];
    for(int i = 0; i<lenad; i++) addr_copy[i] = addr[i];

    const char divider[] = ".";
    char *token = strtok(addr_copy, divider);
    int counter = 0;

    while (token != NULL){
        if (*token == '0') return false;
        int number = str_num_to_int_num(token);
        if(number > 255 || number < 0) return false;
        counter++;
        token = strtok(NULL, divider);
    }

    if(counter != 4) return false;
    return true;
}

#include <stdio.h>
int main() {

    printf("%d\n", is_valid_ip("61.61.1.89"));

    return 0;
}