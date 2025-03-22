#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

struct bmp_header* read_bmp_header(FILE* stream) {
    if (stream == NULL) return NULL;

    struct bmp_header* header = (struct bmp_header*)malloc(sizeof(struct bmp_header));
    if (header == NULL) return NULL;

    if (fread(header, sizeof(struct bmp_header), 1, stream) != 1){
        free(header);
        return NULL;
    }

    if (header->type != 0x4D42) {
        printf("Error: This is not a BMP file.\n");
        free(header);
        return NULL;
    }

    return header;
}


struct pixel *read_data(FILE *stream, const struct bmp_header *header){
    if (stream == NULL || header == NULL) return NULL;

    fseek(stream, header->offset, SEEK_SET);

    uint32_t data_size = header->size - header->offset;
    uint32_t pixel_count = data_size / sizeof(struct pixel);

    struct pixel *data = (struct pixel *)malloc(sizeof(struct pixel) * pixel_count);
    if (data == NULL) return NULL;

    if (fread(data, sizeof(struct pixel), pixel_count, stream) != pixel_count){
        free(data);
        return NULL;
    }

    return data;
}

struct bmp_image *read_bmp(FILE *stream){
    if (stream == NULL) return NULL;

    struct bmp_header *header = read_bmp_header(stream);
    if (header == NULL) return NULL;

    struct bmp_image *image = (struct bmp_image *)malloc(sizeof(struct bmp_image));
    if (image == NULL){
        free(header);
        return NULL;
    }

    image->header = header;
    image->data = read_data(stream, header);
    if (image->data == NULL){
        free(header);
        free(image);
        printf("Error: Corrupted BMP file.\n");
        return NULL;
    }

    return image;
}

bool write_bmp(FILE *stream, const struct bmp_image *image){
    if (stream == NULL || image == NULL) return false;

    if (fwrite(image->header, sizeof(struct bmp_header), 1, stream) != 1)
        return false;

    uint32_t pixel_count = image->header->width * image->header->height;
    if (fwrite(image->data, sizeof(struct pixel), pixel_count, stream) != pixel_count)
        return false;

    return true;
}

void free_bmp_image(struct bmp_image *image){
    if (image != NULL){
        if (image->header != NULL) free(image->header);
        if (image->data != NULL) free(image->data);
        free(image);
    }
}