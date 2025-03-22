#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hof.h"

int cmp_by_score(const void* n1, const void* n2){
    struct player *number_1 = (struct player*)n1; 
    struct player *number_2 = (struct player*)n2; 
    
    if (number_1->score < number_2->score) return 1;
    else if (number_1->score > number_2->score) return -1;
    return 0;
}

char *sliceString(char *str, int start, int end){
    int size = (end - start) + 2;
    char *output = (char *)calloc(10, sizeof(char));

    for (int i = 0; start <= end; start++, i++)
        output[i] = str[start];

    output[size] = '\0';

    return output;
}



int load(struct player list[]){
    FILE* file = fopen(HOF_FILE, "r");
    if(file == NULL){
        exit(0);
        return -1;
    }
    int lines = 0;
    int len = 255;
    char buffer[len];
    int counter = 0;
    int space_indx = 0;

    while(fgets(buffer, len, file)){
        if(lines == 10) break;

        while(buffer[counter] != '\n') counter++;
        while(buffer[space_indx] != ' ') space_indx++;
        
        char* name = sliceString(buffer, 0, space_indx-1);
        char* score = sliceString(buffer, space_indx+1, counter-1);

        strcpy(list[lines].name, name);
        list[lines].score = atoi(score);

        counter = 0;
        space_indx = 0;

        free(name);
        name = NULL;
        free(score);
        score = NULL;

        lines++;

    }
    fclose(file);

    qsort(list, (size_t)lines, sizeof(struct player), cmp_by_score);
    return lines;
}

bool save(const struct player list[], const int size){
    if(size < 0 || size > 10) return false;
    FILE* file = fopen(HOF_FILE, "w");
    if(file == NULL){
        exit(0);
        return false;
    }
    if(size != 0)
        for(int i = 0; i<size; i++) fprintf(file, "%s%s%d\n", list[i].name, DELIMITER, list[i].score);
    
    fclose(file);
    return true;
}

bool add_player(struct player list[], int* size, const struct player player){
    if(*size == 0){	
   	strcpy(list[0].name, player.name);
        list[0].score = player.score;
	*size = *size + 1; 
	return true;
    }
    if(*size < 0 || *size > 10) return false;
    if(list[*size-1].score > player.score && *size == 10) return false;

    int indx = 0;
    for(int i = 0; i < *size; i++){
        if(player.score >= list[i].score) break;
        indx++;
    }
    if(indx == *size && *size < 10){
        strcpy(list[indx].name, player.name);
        list[indx].score = player.score;
        *size = *size + 1; 
        return true;
    }

    for(int i = *size-1; i >= 0; i--){
        if(i == indx && i != 9){
            strcpy(list[i+1].name, list[i].name);
            list[i+1].score = list[i].score;
            strcpy(list[i].name, player.name);
            list[i].score = player.score;
	        if(*size < 10) *size = *size + 1; 
            return true;
        } 
        else if(i == indx && i == 9){
            strcpy(list[i].name, player.name);
            list[i].score = player.score;
            return true;
        }
        else if(i != 9 && i != indx){
            strcpy(list[i+1].name, list[i].name);
            list[i+1].score = list[i].score;
        } 
    }
    return false;
}

