#pragma once

#include <stdint.h>

struct pixel {
    uint8_t b, g, r;
};

struct image {
  uint64_t width, height;
  struct pixel* data;
};

void free_image(const struct image *img);

struct image create_image(uint64_t width, uint64_t height);

struct pixel get_pixel(struct image *img, uint64_t i, uint64_t j);

void set_pixel(struct image *img, struct pixel pixel, uint64_t i, uint64_t j);

struct image img_copy(struct image* img);
