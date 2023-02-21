#include "bmp.h"
#include "header.h"

struct bmp_header create_header(uint64_t width, uint64_t height) {
    uint64_t img_size = sizeof(struct pixel) * width * height;
    	return (struct bmp_header) {
				.bfType = H_TYPE,
            	.bfileSize = H_SIZE + img_size,
            	.bfReserved = H_RESERVED,
            	.bOffBits = H_SIZE,
            	.biSize = H_INFO,
            	.biWidth = width,
            	.biHeight = height,
            	.biPlanes = H_PLANES,
            	.biBitCount = H_BITCOUNT,
            	.biCompression = H_COMPRESSION,
            	.biSizeImage = img_size,
            	.biXPelsPerMeter = H_XMETR,
            	.biYPelsPerMeter = H_YMETR,
            	.biClrUsed = H_NCOLORS,
            	.biClrImportant = H_NIMPORTANT
	};
}

enum read_status get_header(FILE* file, struct bmp_header* header) {
	if (fread(header, sizeof(struct bmp_header), 1, file) != 1) {
		return READ_INVALID_HEADER;
	} else {
		return READ_OK;
	}
}

