#include "bmp.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

char* reverse(const char* text){
    if(text==NULL) return NULL;

    int text_len = strlen(text);
    char* text_copy = calloc(text_len, sizeof(char*));
    int index = -1;
    for (int i = text_len-1; i>=0; i--){
        index++;
        text_copy[index] = toupper(text[i]);
    }
    text_copy[text_len] = '\0';
    return text_copy;
}

char* vigenere_encrypt(const char* key, const char* text){
    if(text==NULL || key==NULL || strcmp(key, "")==0 || strcmp(text, "")==0) return NULL;

    int key_len = strlen(key);
    int text_len = strlen(text);
    int key_indx = -1;

    char* result = calloc(text_len, sizeof(char*));

    for(int i =0; i<text_len; i++){
        char x;
        if (key_indx>=key_len-1) key_indx=-1;
        if (isalpha(text[i])){
            key_indx++;
            if(!isalpha(key[key_indx])) return NULL;
            x = ((toupper(text[i]) + toupper(key[key_indx])) %26)+'A';
        }
        else
            x = text[i];
        result[i] = x;
    }
    result[text_len] = '\0';

    return result;
}

char* vigenere_decrypt(const char* key, const char* text){
    if(text==NULL || key==NULL || strcmp(key, "")==0 || strcmp(text, "")==0) return NULL;

    int key_len = strlen(key);
    int text_len = strlen(text);
    int key_indx = -1;

    char* result = calloc(text_len, sizeof(char*));
    for(int i =0; i<text_len; i++){

        char x;
        if (key_indx>=key_len-1) key_indx=-1;
        if (isalpha(text[i])){
            key_indx++;
            if(!isalpha(key[key_indx])) return NULL;
            x = ((toupper(text[i]) - toupper(key[key_indx]) + 26) %26)+'A';
        }
        else
            x = text[i];
        result[i] = x;
    }
    result[text_len] = '\0';

    return result;
}

// Additional functions to the bit_encrypt/bit_decrypt functions
unsigned int_to_binary(unsigned num) {
    if (num == 0) return 0;
    return (num % 2) + 10 * int_to_binary(num / 2);
}

int binary_to_int(unsigned num) {
    if (num == 0)
        return 0;
    return (num % 10) + 2 * binary_to_int(num / 10);
}

void conv_int_binary_to_char(char* str, int num_of_bit){
    int len_str = strlen(str);

    if(len_str < num_of_bit){
        char tmp_num[len_str];
        strcpy(tmp_num, str);
        for (int i = 0; i<num_of_bit-len_str; i++){
            str[i] = '0';
        }
        str[num_of_bit-len_str] = '\0';
        strcat(str, tmp_num);
    }
}

void swap_bit(char* binary_string){
    char tmp_char = binary_string[0];
    binary_string[0] = binary_string[1];
    binary_string[1] = tmp_char;

    tmp_char = binary_string[2];
    binary_string[2] = binary_string[3];
    binary_string[3] = tmp_char;
}

int refactoring_binary(int binary_num){
    // convert int binary to char*
    char* binary_string = calloc(8, sizeof(char*));
    sprintf(binary_string, "%d", binary_num);
    conv_int_binary_to_char(binary_string, 8);

    // swap two chars between each other
    swap_bit(binary_string);

    // make number to XOR them
    int first_num, second_num;
    char tmp_half[8] = "";
    strncpy(tmp_half, binary_string, 4);
    first_num = atoi(tmp_half);
    tmp_half[0] = '\0';
    strncpy(tmp_half, binary_string+4, 8);
    second_num = atoi(tmp_half);

    // make XOR
    int result_of_XOR = binary_to_int(first_num) ^ binary_to_int(second_num);

    // convert result_of_XOR(int) to char*
    char last_4_bit[5];
    sprintf(last_4_bit, "%d", int_to_binary(result_of_XOR));
    conv_int_binary_to_char(last_4_bit, 4);

    // marge the two parts together
    binary_string[4] = '\0';
    strcat(binary_string, last_4_bit);
    int result = atoi(binary_string);
    free(binary_string);
    return result;
}

int unrefactoring_binary(int binary_num){
    // convert int binary to char*
    char* binary_string = calloc(8, sizeof(char*));
    sprintf(binary_string, "%d", binary_num);
    conv_int_binary_to_char(binary_string, 8);

    // make number to XOR them
    int first_num, second_num;
    char tmp_half[8] = "";
    strncpy(tmp_half, binary_string, 4);
    first_num = atoi(tmp_half);
    tmp_half[0] = '\0';
    strncpy(tmp_half, binary_string+4, 8);
    second_num = atoi(tmp_half);

    int result_of_XOR = binary_to_int(first_num) ^ binary_to_int(second_num);

    // swap two chars between each other
    swap_bit(binary_string);

    // convert result_of_XOR(int) to char*
    char last_4_bit[5];
    sprintf(last_4_bit, "%d", int_to_binary(result_of_XOR));
    conv_int_binary_to_char(last_4_bit, 4);

    // marge the two parts together
    binary_string[4] = '\0';
    strcat(binary_string, last_4_bit);
    int result = atoi(binary_string);    
    free(binary_string);
    return result;
}


unsigned char* bit_encrypt(const char* text){
    if(text==NULL || strcmp(text, "")==0) return NULL;
    int len_text = strlen(text);
    unsigned char* result = calloc(len_text, sizeof(unsigned char*));
    for(int i = 0; i<len_text; i++)
        result[i] = binary_to_int(refactoring_binary(int_to_binary(text[i])));
   return result;
}

char* bit_decrypt(const unsigned char* text){
    if(text==NULL || strcmp((const char*)text, "")==0) return NULL;
    int len_text = strlen((char*)text);
    char* result = calloc(len_text, sizeof(char));
    for(int i = 0; i<len_text; i++)
        result[i] = binary_to_int(unrefactoring_binary(int_to_binary(text[i])));
    return result;
}

unsigned char* bmp_encrypt(const char* key, const char* text){
    if(text==NULL || key==NULL || strcmp(key, "")==0 || strcmp(text, "")==0) return NULL;
    return bit_encrypt(vigenere_encrypt(key, reverse(text)));
}

char* bmp_decrypt(const char* key, const unsigned char* text){
    if(text==NULL || key==NULL || strcmp(key, "")==0 || strcmp((const char*)text, "")==0) return NULL;
    return reverse(vigenere_decrypt(key, bit_decrypt(text)));
}
