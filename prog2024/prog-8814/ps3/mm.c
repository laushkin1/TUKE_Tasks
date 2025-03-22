#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mm(char* num_str);

int main(){
    char* userinput = calloc(100101, sizeof(char));
    scanf("%s", userinput);
    int result = mm(userinput);
    free(userinput);
    userinput = NULL;
    printf("%d\n", result);
    return 0;
}

int mm(char* num_str){
    int counter = 0;
    for(int i = 0, len=(int)strlen(num_str); i<len; i++){
        if(num_str[i] >= '0' && num_str[i] <= '9'){
            counter+=(num_str[i]-'0');
        }
    }
    if(counter>=10){
        char res_str[2560];
        sprintf(res_str, "%d", counter);
        return mm(res_str);
    }
    return counter;
}
