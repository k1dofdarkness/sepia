#include "image.h"
#include "sepia.h"
#include <math.h>
#include <stddef.h>

static uint8_t sat(uint64_t x) {
    if (x < 256)
        return x;
    return 255;
}

void sepia(struct image* img) {
    uint64_t img_size = img->height * img->width;
    for (uint64_t i = 0; i <= img_size; i++) {
            float sepia_red = sat(roundf((img->data + i)->r * 0.393  + (img->data + i)->g * 0.769 + (img->data + i)->b * 0.189));
            float sepia_green = sat(roundf((img->data + i)->r * 0.349 + (img->data + i)->g * 0.686 + (img->data + i)->b * 0.168));
            float sepia_blue = sat(roundf((img->data + i)->r * 0.272 + (img->data + i)->g * 0.534 + (img->data + i)->b * 0.131));
            (img->data + i)->r = sepia_red;
            (img->data + i)->g = sepia_green;
            (img->data + i)->b = sepia_blue;
    }
}

void sepia_asm_impl(struct image* img) {
  uint64_t img_size = img->height * img->width;
  struct image old_img = img_copy(img);
  uint64_t iter_count = (img_size - img_size % 4) * 3;
  sepia_asm(old_img.data, img->data, iter_count);
  for (uint64_t i = 0; i <= img_size % 4; i++) {
            float sepia_red = sat(roundf((img->data + i)->r * 0.393  + (img->data + i)->g * 0.769 + (img->data + i)->b * 0.189));
            float sepia_green = sat(roundf((img->data + i)->r * 0.349 + (img->data + i)->g * 0.686 + (img->data + i)->b * 0.168));
            float sepia_blue = sat(roundf((img->data + i)->r * 0.272 + (img->data + i)->g * 0.534 + (img->data + i)->b * 0.131));
            (img->data + i)->r = sepia_red;
            (img->data + i)->g = sepia_green;
            (img->data + i)->b = sepia_blue;
  }
}

