#pragma once

#define H_TYPE 0x4D42
#define H_RESERVED 0
#define H_SIZE 54
#define H_INFO 40
#define H_PLANES 1
#define H_BITCOUNT 24
#define H_COMPRESSION 0
#define H_XMETR 0
#define H_YMETR 0
#define H_NCOLORS 0
#define H_NIMPORTANT 0

#include "bmp.h"
#include "image.h"

#pragma pack(push, 1)
struct bmp_header {
        uint16_t bfType;
        uint32_t bfileSize;
        uint32_t bfReserved;
        uint32_t bOffBits;
        uint32_t biSize;
        uint32_t biWidth;
        uint32_t biHeight;
        uint16_t biPlanes;
        uint16_t biBitCount;
        uint32_t biCompression;
        uint32_t biSizeImage;
        uint32_t biXPelsPerMeter;
        uint32_t biYPelsPerMeter;
        uint32_t biClrUsed;
        uint32_t biClrImportant;
};
#pragma pack(pop)

struct bmp_header create_header(uint64_t width, uint64_t height);

enum read_status get_header(FILE* file, struct bmp_header* header);

