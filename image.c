#include "image.h"
#include <stdlib.h>
#include <string.h>

struct image create_image(uint64_t width, uint64_t height) {
	struct pixel* data = (struct pixel*)malloc(width * height * sizeof(struct pixel));
	if (data == NULL) {
        struct image empty_img = {0};
        return empty_img;
    }
	return (struct image) {
		.width = width, 
		.height = height, 
		.data = data
	};
}

void free_image(const struct image *img) {
	free(img->data);
}

struct pixel get_pixel(struct image *img, uint64_t i, uint64_t j) {
    return img->data[img->width * j + i];
}

void set_pixel(struct image *img, struct pixel pixel, uint64_t i, uint64_t j) {
    img->data[img->width * j + i] = pixel;
}

struct image img_copy(struct image* img) {
    struct image img_copy = create_image(img->width, img->height);
    memcpy(img_copy.data, img->data, sizeof(struct pixel) * img->width * img->height);
    return img_copy;
}
