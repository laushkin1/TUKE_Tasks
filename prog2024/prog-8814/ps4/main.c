#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "bmp.h"
#include "transformations.h"

int main(){
    FILE *stream = fopen("assets/picaxe.bmp", "rb");
    if (stream == NULL){
        printf("Error: Unable to open file.\n");
        return EXIT_FAILURE;
    }

    struct bmp_image *image = read_bmp(stream);
    if (image == NULL){
        printf("Error: Unable to read BMP file.\n");
        fclose(stream);
        return EXIT_FAILURE;
    }

    fclose(stream);

    struct bmp_image *flipped_horizontally = flip_horizontally(image);
    struct bmp_image *flipped_vertically = flip_vertically(image);
    struct bmp_image *rotated_right = rotate_right(image);
    struct bmp_image *rotated_left = rotate_left(image);
    struct bmp_image *cropped = crop(image, 10, 10, 100, 100);
    struct bmp_image *scaled = scale(image, 2.0);
    struct bmp_image *extracted = extract(image, "rgb");

    // Free memory
    free_bmp_image(image);
    free_bmp_image(flipped_horizontally);
    free_bmp_image(flipped_vertically);
    free_bmp_image(rotated_right);
    free_bmp_image(rotated_left);
    free_bmp_image(cropped);
    free_bmp_image(scaled);
    free_bmp_image(extracted);

    struct bmp_image *image1 = (struct bmp_image *)malloc(sizeof(struct bmp_image));
    if (image1 == NULL){
        printf("Error: Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    image1->header = (struct bmp_header *)malloc(sizeof(struct bmp_header));
    if (image1->header == NULL){
        printf("Error: Memory allocation failed.\n");
        free(image1);
        return EXIT_FAILURE;
    }

    image1->header->type = 0x4D42;
    image1->header->size = sizeof(struct bmp_header);

    image1->data = (struct pixel *)malloc(sizeof(struct pixel) * 100);
    if (image1->data == NULL){
        printf("Error: Memory allocation failed.\n");
        free(image1->header);
        free(image1);
        return EXIT_FAILURE;
    }

    FILE *file = fopen("assets/freddy.bmp", "wb");
    if (file == NULL){
        printf("Error: Unable to open file for writing.\n");
        free(image1->header);
        free(image1->data);
        free(image1);
        return EXIT_FAILURE;
    }

    if (!write_bmp(file, image1)){
        printf("Error: Unable to write BMP image.\n");
        fclose(file);
        free_bmp_image(image1);
        return EXIT_FAILURE;
    }
    
    fclose(file);
    free_bmp_image(image1);

    return EXIT_SUCCESS;
}
