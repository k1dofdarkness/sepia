#include "bmp.h"
#include "header.h"
#include "image.h"
#include "sepia.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>


#define NUM_OF_ARGS 4
#define ERROR_CODE 1
#define SUCCESS_CODE 0
#define C_KEY "-C"
#define ASM_KEY "-asm"

int main(int argc, char** argv) {
    bool func_key;
	if (argc != NUM_OF_ARGS) {
		printf("Неправильный ввод. Введите команду в формате: ./main <input.bmp> <output.bmp> <(-C/-asm)>\n");
		return ERROR_CODE;
	}
    
	if (!strcmp(argv[3], C_KEY)) {
		func_key = true;
	} else if (!strcmp(argv[3], ASM_KEY)) {
		func_key = false;
	} else {
		printf("Неправильный ввод. Введите ключ -C или -asm!\n");
		return ERROR_CODE;
	}

    FILE *input = fopen(argv[1], "rb");
    FILE *output = fopen(argv[2], "wb");

    if (input == NULL) {
        printf("Файл не может быть открыт\n");
        return ERROR_CODE;
    }

    struct image img = {0};

    if (from_bmp(input, &img) != READ_OK) {
        printf("Ошибка чтения изображения!\n");
        free_image(&img);
        fclose(input);
        fclose(output);
        return ERROR_CODE;
    }

    double time_spent = 0.0;
    clock_t begin = clock();

	if (func_key) {
		sepia(&img);		
	} else {
        sepia_asm_impl(&img);
    }

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Время выполнения %f секунд.\n", time_spent);

    if (to_bmp(output, &img) != WRITE_OK) {
        printf("Ошибка! Не получается сохранить изображение!\n");
        free_image(&img);
        fclose(input);
        fclose(output);
        return ERROR_CODE;
    }

    printf("Изображение успешно сохранено.\n");
    free_image(&img);
    fclose(input);
    fclose(output);
	return SUCCESS_CODE;
}

