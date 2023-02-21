#include "bmp.h"
#include "header.h"
#include <stdlib.h>

uint8_t calc_padding(uint64_t width) {
    return 4 - (width * sizeof(struct pixel)) % 4;
}

enum read_status get_pixels( FILE* file, struct image *img ) {
    uint8_t padding = calc_padding(img->width);
    for (size_t i = 0; i < img->height; i++) {
        if (fread(img->data + (i * img->width), sizeof(struct pixel), img->width, file) != img->width) {
			return READ_INVALID_SIGNATURE;
		}
		if (fseek(file, padding, SEEK_CUR) != 0) {
			return READ_INVALID_SIGNATURE;
		}
    }
    return READ_OK;
}

enum write_status wr_bmp(FILE* file, const struct image* img) {
	for (size_t i = 0; i < img->height; i++) {
		if (fwrite(img->data + i * img->width, sizeof(struct pixel), img->width, file) != img->width){
			return WRITE_ERROR;
		}
		if (fseek(file, calc_padding(img->width), SEEK_CUR) != 0) {
			return WRITE_ERROR;
		}
	}
	return WRITE_OK;
}

enum read_status from_bmp(FILE* in, struct image* img) {
    struct bmp_header header = {0};
    if (get_header(in, &header) != READ_OK) {
        return READ_INVALID_HEADER;
    }
    *img = create_image(header.biWidth, header.biHeight);

    enum read_status status = get_pixels(in, img);
    if (status != READ_OK) {
        free_image(img);
        return status;
    }
    return READ_OK;
}


enum write_status to_bmp(FILE* output, struct image const* img) {
	struct bmp_header header = create_header(img->width, img->height);
	if (fwrite(&header, sizeof(struct bmp_header), 1, output) != 1) {
		return WRITE_ERROR;
	}
	return wr_bmp(output, img);
}
