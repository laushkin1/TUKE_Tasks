#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "transformations.h"

struct bmp_image *copy_image(const struct bmp_image *image);

struct bmp_header *copy_header(const struct bmp_header *header);

struct pixel *copy_pixels(const struct pixel *pixels, uint32_t width, uint32_t height);

struct bmp_image *flip_horizontally(const struct bmp_image *image) {
    if (image == NULL) return NULL;

    struct bmp_image *flipped_image = copy_image(image);
    if (flipped_image == NULL) return NULL;

    for (int y = 0, h = flipped_image->header->height; y < h; ++y) {
        for (int x = 0, w = flipped_image->header->width; x < w; ++x)
            flipped_image->data[y * w + x] = image->data[y * w + (w - 1 - x)];
    }

    return flipped_image;
}

struct bmp_image *flip_vertically(const struct bmp_image *image) {
    if (image == NULL) return NULL;

    struct bmp_image *flipped_image = copy_image(image);
    if (flipped_image == NULL) return NULL;

    for (int y = 0, h = flipped_image->header->height; y < h; ++y) {
        for (int x = 0, w = flipped_image->header->width; x < w; ++x)
            flipped_image->data[y * w + x] = image->data[(h - 1 - y) * w + x];
    }

    return flipped_image;
}

struct bmp_image *rotate_right(const struct bmp_image *image) {
    if (image == NULL) return NULL;

    struct bmp_image *rotated_image = (struct bmp_image *) malloc(sizeof(struct bmp_image));
    if (rotated_image == NULL) return NULL;

    rotated_image->header = copy_header(image->header);
    if (rotated_image->header == NULL) {
        free(rotated_image);
        return NULL;
    }

    rotated_image->header->width = image->header->height;
    rotated_image->header->height = image->header->width;

    rotated_image->data = (struct pixel *) malloc(
            rotated_image->header->width * rotated_image->header->height * sizeof(struct pixel));
    if (rotated_image->data == NULL) {
        free(rotated_image->header);
        free(rotated_image);
        return NULL;
    }

    for (int y = 0, h = rotated_image->header->height; y < h; ++y) {
        for (int x = 0, w = rotated_image->header->width; x < w; ++x)
            rotated_image->data[y * w + x] = image->data[(image->header->height - 1 - x) * image->header->width + y];
    }

    return rotated_image;
}

struct bmp_image *rotate_left(const struct bmp_image *image) {
    if (image == NULL) return NULL;

    struct bmp_image *rotated_image = (struct bmp_image *) malloc(sizeof(struct bmp_image));
    if (rotated_image == NULL) return NULL;

    rotated_image->header = copy_header(image->header);
    if (rotated_image->header == NULL) {
        free(rotated_image);
        return NULL;
    }

    rotated_image->header->width = image->header->height;
    rotated_image->header->height = image->header->width;

    rotated_image->data = (struct pixel *) malloc(
            rotated_image->header->width * rotated_image->header->height * sizeof(struct pixel));
    if (rotated_image->data == NULL) {
        free(rotated_image->header);
        free(rotated_image);
        return NULL;
    }

    for (int y = 0, h = rotated_image->header->height; y < h; ++y) {
        for (int x = 0, w = rotated_image->header->width; x < w; ++x)
            rotated_image->data[y * w + x] = image->data[x * image->header->width + (image->header->width - 1 - y)];
    }

    return rotated_image;
}

struct bmp_image *
crop(const struct bmp_image *image, const uint32_t start_y, const uint32_t start_x, const uint32_t height,
     const uint32_t width) {
    if (image == NULL || start_y >= image->header->height ||
        start_x >= image->header->width || height < 1 || width < 1 ||
        start_y + height > image->header->height ||
        start_x + width > image->header->width)
        return NULL;

    struct bmp_image *cropped_image = (struct bmp_image *) malloc(sizeof(struct bmp_image));
    if (cropped_image == NULL) return NULL;

    cropped_image->header = (struct bmp_header *) malloc(sizeof(struct bmp_header));
    if (cropped_image->header == NULL) {
        free(cropped_image);
        return NULL;
    }
    memcpy(cropped_image->header, image->header, sizeof(struct bmp_header));

    cropped_image->header->width = width;
    cropped_image->header->height = height;

    cropped_image->data = (struct pixel *) malloc(height * width * sizeof(struct pixel));
    if (cropped_image->data == NULL) {
        free(cropped_image->header);
        free(cropped_image);
        return NULL;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x)
            cropped_image->data[y * width + x] = image->data[(start_y + y) * image->header->width + (start_x + x)];
    }

    return cropped_image;
}

struct bmp_image *scale(const struct bmp_image *image, float factor) {
    if (image == NULL || factor == 0) return NULL;

    struct bmp_image *scaled_image = (struct bmp_image *) malloc(sizeof(struct bmp_image));
    if (scaled_image == NULL) return NULL;

    scaled_image->header = (struct bmp_header *) malloc(sizeof(struct bmp_header));
    if (scaled_image->header == NULL) {
        free(scaled_image);
        return NULL;
    }
    memcpy(scaled_image->header, image->header, sizeof(struct bmp_header));

    if (factor != 1) {
        scaled_image->header->width = round(image->header->width * factor);
        scaled_image->header->height = round(image->header->height * factor);
    }

    scaled_image->data = (struct pixel *) malloc(
            scaled_image->header->width * scaled_image->header->height * sizeof(struct pixel));
    if (scaled_image->data == NULL) {
        free(scaled_image->header);
        free(scaled_image);
        return NULL;
    }

    for (int y = 0; y < scaled_image->header->height; ++y) {
        for (int x = 0; x < scaled_image->header->width; ++x) {
            float source_x = x * (image->header->width - 1) / (float) (scaled_image->header->width - 1);
            float source_y = y * (image->header->height - 1) / (float) (scaled_image->header->height - 1);
            int source_x_floor = floor(source_x);
            int source_y_floor = floor(source_y);
            int source_x_ceil = ceil(source_x);
            int source_y_ceil = ceil(source_y);
            float x_weight = source_x - source_x_floor;
            float y_weight = source_y - source_y_floor;

            struct pixel p1 = image->data[source_y_floor * image->header->width + source_x_floor];
            struct pixel p2 = image->data[source_y_floor * image->header->width + source_x_ceil];
            struct pixel p3 = image->data[source_y_ceil * image->header->width + source_x_floor];
            struct pixel p4 = image->data[source_y_ceil * image->header->width + source_x_ceil];

            struct pixel interpolated_pixel;
            interpolated_pixel.blue = p1.blue * (1 - x_weight) * (1 - y_weight) + p2.blue * x_weight * (1 - y_weight) +
                                      p3.blue * (1 - x_weight) * y_weight + p4.blue * x_weight * y_weight;
            interpolated_pixel.green =
                    p1.green * (1 - x_weight) * (1 - y_weight) + p2.green * x_weight * (1 - y_weight) +
                    p3.green * (1 - x_weight) * y_weight + p4.green * x_weight * y_weight;
            interpolated_pixel.red = p1.red * (1 - x_weight) * (1 - y_weight) + p2.red * x_weight * (1 - y_weight) +
                                     p3.red * (1 - x_weight) * y_weight + p4.red * x_weight * y_weight;

            scaled_image->data[y * scaled_image->header->width + x] = interpolated_pixel;
        }
    }

    return scaled_image;
}

struct bmp_image *extract(const struct bmp_image *image, const char *colors_to_keep) {
    if (image == NULL || colors_to_keep == NULL || strlen(colors_to_keep) == 0)
        return NULL;

    for (int i = 0, len = strlen(colors_to_keep); i < len; i++) {
        if (colors_to_keep[i] != 'b' && colors_to_keep[i] != 'g' && colors_to_keep[i] != 'r')
            return NULL;
    }

    struct bmp_image *extracted_image = (struct bmp_image *) malloc(sizeof(struct bmp_image));
    if (extracted_image == NULL) return NULL;

    extracted_image->header = (struct bmp_header *) malloc(sizeof(struct bmp_header));
    if (extracted_image->header == NULL) {
        free(extracted_image);
        return NULL;
    }
    memcpy(extracted_image->header, image->header, sizeof(struct bmp_header));

    size_t pixel_data_size = image->header->width * image->header->height * sizeof(struct pixel);
    extracted_image->data = (struct pixel *) malloc(pixel_data_size);
    if (extracted_image->data == NULL) {
        free(extracted_image->header);
        free(extracted_image);
        return NULL;
    }

    for (int i = 0, s = image->header->width * image->header->height; i < s; i++) {
        struct pixel *original_pixel = &image->data[i];
        struct pixel *extracted_pixel = &extracted_image->data[i];

        if (strchr(colors_to_keep, 'b') != NULL)
            extracted_pixel->blue = original_pixel->blue;
        else extracted_pixel->blue = 0;

        if (strchr(colors_to_keep, 'g') != NULL)
            extracted_pixel->green = original_pixel->green;
        else extracted_pixel->green = 0;

        if (strchr(colors_to_keep, 'r') != NULL)
            extracted_pixel->red = original_pixel->red;
        else extracted_pixel->red = 0;
    }

    return extracted_image;
}

struct bmp_image *copy_image(const struct bmp_image *image) {
    if (image == NULL) return NULL;

    struct bmp_image *copied_image = (struct bmp_image *) malloc(sizeof(struct bmp_image));
    if (copied_image == NULL) return NULL;

    copied_image->header = copy_header(image->header);
    if (copied_image->header == NULL) {
        free(copied_image);
        return NULL;
    }

    copied_image->data = copy_pixels(image->data, image->header->width, image->header->height);
    if (copied_image->data == NULL) {
        free(copied_image->header);
        free(copied_image);
        return NULL;
    }

    return copied_image;
}

struct bmp_header *copy_header(const struct bmp_header *header) {
    if (header == NULL) return NULL;

    struct bmp_header *copied_header = (struct bmp_header *) malloc(sizeof(struct bmp_header));
    if (copied_header == NULL) return NULL;

    memcpy(copied_header, header, sizeof(struct bmp_header));
    return copied_header;
}

struct pixel *copy_pixels(const struct pixel *pixels, uint32_t width, uint32_t height) {
    if (pixels == NULL) return NULL;

    struct pixel *copied_pixels = (struct pixel *) malloc(width * height * sizeof(struct pixel));
    if (copied_pixels == NULL) return NULL;

    memcpy(copied_pixels, pixels, width * height * sizeof(struct pixel));
    return copied_pixels;
}