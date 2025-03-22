#include "playfair.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

// remove char from str
void removeChar(char *str, char c) {
    int i, j;
    int len = strlen(str);
    for (i = j = 0; i < len; i++) {
        if (str[i] != c) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

// code below should find index of first '*' and put toupper(key_copy[i])(char) at this place
void matrixWrite(char matrix[5][5], char c){
    char *ptr = strchr(matrix[0], '*');
    if(ptr){
        int index = ptr - matrix[0];
        if(index<5) matrix[0][index] = c;
        else if (index>=5 && index<10) matrix[1][index-5] = c;
        else if (index>=10 && index<15) matrix[2][index-10] = c;
        else if (index>=15 && index<20) matrix[3][index-15] = c;
        else if (index>=20 && index<25) matrix[4][index-20] = c;
    }
}

// func that refactoring text
char* makeTextCorrect(const char* text, char* output_text, int text_len){
    char* res = calloc((text_len+1), sizeof(char*));
    if (res == NULL) {
        exit(1);
    }
    strcpy(res, text);

    for (int i = 0; i < text_len; i++){
        if (res[i] == 'W') res[i] = 'V';
        if (i % 2 == 0){
            // put X between same letter
            if (i + 1 < text_len && text[i] == text[i+1] && text[i] != 'X' && text[i] > 32 && text[i]){
                char* second_half = calloc((text_len-i), sizeof(char*));
                if (second_half == NULL) {
                    exit(1);
                }

                strcpy(second_half, text+i);
                res[i] = text[i+1];
                res[i+1] = '\0';
                second_half[0] = 'X';
                strcat(res, second_half);
                free(second_half);

                return makeTextCorrect(res, output_text, text_len);
            }
            // remove space
            else if(text[i] == ' ' && i+1 < text_len){
                char* second_half = strchr(text+i, text[i+1]);
                if(second_half != NULL){
                    int indx = second_half - text;   
                    res[indx-1] = '\0';
                    strcat(res, second_half);
                    return makeTextCorrect(res, output_text, text_len);
                }
            }
        }
    }
    for (int i = 0; res[i] != '\0'; i++){
        if(text[i] == ' ' && i+1 < text_len){
            char* second_half = strchr(text+i, text[i+1]);
            if(second_half != NULL){
                int indx = second_half - text;
                res[indx-1] = '\0';
                strcat(res, second_half);
                return makeTextCorrect(res, output_text, text_len);
            }
        }
    }


    if(strlen(res) % 2 != 0) strcat(res, "X");
    output_text[0] = '\0';
    strcat(output_text, res);
    free(res);
    return "return";
}

// func return array of int -> int[y][x] of matrix
int* findMatrixIndex(char matrix[5][5], char c){
    static int r[2];
    char *ptr = strchr(matrix[0], toupper(c));
    if(ptr){
        int index = ptr - matrix[0];
        if(index<5) {
            r[0] = 0;
            r[1] = index;
        }
        else if (index>=5 && index<10){
            r[0] = 1;
            r[1] = index-5;
        }
        else if (index>=10 && index<15){
            r[0] = 2;
            r[1] = index-10;
        }
        else if (index>=15 && index<20){
            r[0] = 3;
            r[1] = index-15;
        }
        else if (index>=20 && index<25){
            r[0] = 4;
            r[1] = index-20;
        }
        else{
            r[0] = -1;
            r[1] = -1;
        }
    }
    return r;
}

// func that creates a matrix in one click
void makeMatrix(char matrix[5][5], int key_len, const char* key){

    char ALPHA_copy[strlen(ALPHA)+1];
    char key_copy[key_len+1];

    strcpy(ALPHA_copy, ALPHA);
    strcpy(key_copy, key);

    // Add upper letter of key to matrix
    for (int i = 0; i<key_len; i++){
        if (toupper(key_copy[i]) == 'W'){
            key_copy[i] = 'V';
        }
        // if char 'toupper(key_copy[i])' in ALPHA_copy then remove this char and write in matrix
        if(strchr(ALPHA_copy, toupper(key_copy[i])) != NULL){
            removeChar(ALPHA_copy, toupper(key_copy[i]));
            // "write in matrix"
            matrixWrite(matrix, toupper(key_copy[i]));
        }
    }

    // add the rest of ALPHA_copy to matrix
    for(int i = 0, len_alpha_copy = strlen(ALPHA_copy); i<len_alpha_copy; i++){
        matrixWrite(matrix, ALPHA_copy[i]);
    }
}

bool check_key_param(const char* key, int key_len){
    int counter = 0;
    for (int i = 0; i<key_len; i++){
        if(!isalpha(key[i])){
            if(key[i] != ' ') return false;
        }
        if(key[i] != ' ') counter++;
    }
    return counter;
}

char* playfair_encrypt(const char* key, const char* text){
    if(text==NULL || key==NULL || strcmp(key, "")==0 || strcmp(text, "")==0) return NULL;

    int key_len = strlen(key);
    if(!check_key_param(key, key_len)) return NULL;

    int text_len = strlen(text);
    for (int i = 0; i<text_len; i++){
        if(!isalpha(text[i]))
            if(text[i] != ' ') return NULL;
        
    }

    char matrix[5][5] = {
            {'*', '*', '*', '*', '*'},
            {'*', '*', '*', '*', '*'},
            {'*', '*', '*', '*', '*'},
            {'*', '*', '*', '*', '*'},
            {'*', '*', '*', '*', '*'}
    };
    makeMatrix(matrix, key_len, key);

// --------------------------- // MATRIX IS READY // --------------------------- //

    // make copy of toupper(text)
    char text_copy[text_len];
    strcpy(text_copy, text);
    for(int i = 0; i<text_len; i++){
        text_copy[i] = toupper(text[i]);
    }

    // add X between identical letters in text
    makeTextCorrect(text_copy, text_copy, text_len);
    int copy_text_len = strlen(text_copy);

    char encrypted_text[copy_text_len];
    encrypted_text[0] = '\0';


    // find index of two chars
    for(int i = 0; i<copy_text_len; i++){
        if (i%2 == 1){
            int index_first_char[2] = {findMatrixIndex(matrix, text_copy[i-1])[0],
                                       findMatrixIndex(matrix, text_copy[i-1])[1]};
            int index_second_char[2] = {findMatrixIndex(matrix, text_copy[i])[0],
                                        findMatrixIndex(matrix, text_copy[i])[1]};

            // Main logic of encrypted
            if (index_first_char[1] == index_second_char[1]){
                if (index_first_char[0] < 4) index_first_char[0]++;
                else index_first_char[0]-=4;

                if (index_second_char[0] < 4) index_second_char[0]++;
                else index_second_char[0]-=4;
            } else if (index_first_char[0] == index_second_char[0]){
                if (index_first_char[1] < 4) index_first_char[1]++;
                else index_first_char[1]-=4;

                if (index_second_char[1] < 4) index_second_char[1]++;
                else index_second_char[1]-=4;
            } else {
                int indx_tmp = index_first_char[1];
                index_first_char[1] = index_second_char[1];
                index_second_char[1] = indx_tmp;
            }
            char tmp_chars[3] = {
                    matrix[index_first_char[0]][index_first_char[1]],
                    matrix[index_second_char[0]][index_second_char[1]],
                    ' '
            };
            strcat(encrypted_text, tmp_chars);
        }
    }

    char* result = calloc(strlen(encrypted_text), sizeof(char*));
    strcpy(result, encrypted_text);
    for(int i = 0, l = strlen(result); i<l; i++){
        if(result[i] >= 0 && result[i] < 5) removeChar(result, result[i]); 
    }
    result[strlen(result)-1] = '\0';
    return result;
}


char* playfair_decrypt(const char* key, const char* text){
    if(text==NULL || key==NULL || strcmp(key, "")==0 || strcmp(text, "")==0) return NULL;

    int key_len = strlen(key);
    if(!check_key_param(key, key_len)) return NULL;

    int text_len = strlen(text);
    for (int i = 0; i<text_len; i++){
        if(!isalpha(text[i]))
            if(text[i] != ' ') return NULL; 
        
        if(text[i] == 'W') return NULL;
    }
    char matrix[5][5] = {
            {'*', '*', '*', '*', '*'},
            {'*', '*', '*', '*', '*'},
            {'*', '*', '*', '*', '*'},
            {'*', '*', '*', '*', '*'},
            {'*', '*', '*', '*', '*'}
    };
    makeMatrix(matrix, key_len, key);

// --------------------------- // MATRIX IS READY // --------------------------- //

    char decrypted_text[text_len];
    decrypted_text[0] = '\0';

    // find index of two chars
    int counter = 0;
    for(int i = 0; i<text_len; i++){

        counter++;
        if(text[i] < 32) counter = 0;
        if(counter == 2){
            int index_first_char[2] = {findMatrixIndex(matrix, text[i-1])[0],
                                       findMatrixIndex(matrix, text[i-1])[1]};
            int index_second_char[2] = {findMatrixIndex(matrix, text[i])[0],
                                        findMatrixIndex(matrix, text[i])[1]};

            // Main logic of decrypted
            if (index_first_char[1] == index_second_char[1]){
                if (index_first_char[0] > 0) index_first_char[0]--;
                else index_first_char[0]+=4;

                if (index_second_char[0] > 0) index_second_char[0]--;
                else index_second_char[0]+=4;
            } else if (index_first_char[0] == index_second_char[0]){
                if (index_first_char[1] > 0) index_first_char[1]--;
                else index_first_char[1]+=4;

                if (index_second_char[1] > 0) index_second_char[1]--;
                else index_second_char[1]+=4;
            } else {
                int indx_tmp = index_first_char[1];
                index_first_char[1] = index_second_char[1];
                index_second_char[1] = indx_tmp;
            }

            char tmp_chars[2] = {
                    matrix[index_first_char[0]][index_first_char[1]],
                    matrix[index_second_char[0]][index_second_char[1]]
            };
            strcat(decrypted_text, tmp_chars);

        } else if(counter == 3) counter = 0;
    }

    char* result = calloc(strlen(decrypted_text), sizeof(char*));
    strcpy(result, decrypted_text);

    return result;
}
