#include <stdio.h>
#include <stdlib.h>
#include "playfair.h"
#include "bmp.h"

int main(){
    printf("playfair: \n");
    char *encrypted, *decrypted;

// even length of string
    encrypted = playfair_encrypt("SeCReT", "Hello world");
    printf("%s\n", encrypted);
// "Hello world" --> "HELXLOVORLDX"
// IS JZ JQ XN TK JC
    decrypted = playfair_decrypt("SeCReT", encrypted);
    printf("%s\n", decrypted);
// HELXLOVORLDX
    free(encrypted);
    free(decrypted);
/*
// odd length of string
    encrypted = playfair_encrypt("world", "Hello");
    printf("%s\n", encrypted);
// "Hello" --> "HELXLO"
// JB RY DR
    decrypted = playfair_decrypt("world", encrypted);
    printf("%s\n", decrypted);
// HELXLO
    free(encrypted);
    free(decrypted);

// letter 'X' in message
    encrypted = playfair_encrypt("Password", "Taxi please");
    printf("%s\n", encrypted);
// "Taxi please" --> "TAXIPLEASE"
// UP YH AK DO OB
    decrypted = playfair_decrypt("Password", encrypted);
    printf("%s\n", decrypted);
// TAXIPLEASE
    free(encrypted);
    free(decrypted);

// multi 'X's in message
    encrypted = playfair_encrypt("please", "Taxxxiii");
    printf("%s\n", encrypted);
// "Taxxxiii" --> "TAXXXIIXIX"
// RS EE VJ JV JV
    decrypted = playfair_decrypt("please", encrypted);
    printf("%s\n", decrypted);
// TAXXXIIXIX
    free(encrypted);
    free(decrypted);
//
*/
    printf("\n");
    printf("bmp: \n");
    char key[] = "CoMPuTeR";
    char hello_world[] = "Hello world!";

    char* reversed = reverse(hello_world);
    printf("%s\n", reversed);
// "!DLROW OLLEH"

// basic test with long text
    encrypted = vigenere_encrypt(key, hello_world);
    printf("%s\n", encrypted);
// "JSXAI PSINR!"
    decrypted = vigenere_decrypt(key, encrypted);
    printf("%s\n", decrypted);
// "HELLO WORLD!"

    unsigned char* encrypted_;
    char* decrypted_;
// basic test with long text
    encrypted_ = bit_encrypt(hello_world);
    for(int i=0; i < 12;i++) {
        printf("%x ", encrypted_[i]);
        // 80 9c 95 95 96 11 bc 96 b9 95 9d 10
    }
    printf("\n");

    decrypted_ = bit_decrypt(encrypted_);
    printf("%s\n", decrypted_);
    // Hello world!
    free(decrypted_);
    free(encrypted_);

    printf("\n");
    unsigned char* encrypted_bmp;
    char* decrypted_bmp;
    encrypted_bmp = bmp_encrypt(key, hello_world);
    for(int i=0; i < 12;i++) {
        printf("%x ", encrypted_bmp[i]);
        // 10 8e a0 8c 8c ab 11 80 aa 8b 8f ac
    }
    printf("\n");

    decrypted_bmp = bmp_decrypt(key, encrypted_bmp);
    printf("%s\n", decrypted_bmp);
    // HELLO WORLD!
    free(encrypted_bmp);
    free(decrypted_bmp);


    return 0;
}