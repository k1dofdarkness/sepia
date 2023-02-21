#pragma once

#include "image.h"

void sepia(struct image* img);

void sepia_asm_impl(struct image* img);

extern void sepia_asm(struct pixel* old_pixels, struct pixel* new_pixels, uint64_t size);
